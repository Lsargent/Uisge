/** @file Board.cpp
 */
#include "GlobalDefs.h"

#include "Board.h"
#include "Team.h"
#include "Token.h"
#include "Position.h"
#include "Player.h"


#include <iostream>
using namespace std;

Board::Board(void)
{
/// for each Position (row,column), A <= row <= F , 1 <= column <= HORIZONTAL_DIM on the board, create a new position
    for (ROW row=A; static_cast<unsigned int>(row) <= VERTICAL_DIM; )
    {
	for (COLUMN column=1; column<=HORIZONTAL_DIM;column++)
            {
            mPositions[row-1][column-1]= new Position(row,column);  // Arrays start on zero indexes
            }
	row=static_cast<ROW>(row+1);
    }
}

Board::~Board(void)
{
/// delete each Position (row,column), A <= row <= F , 1 <= column <= HORIZONTAL_DIM on the board

    for (ROW row=A; row <= VERTICAL_DIM;)
    {
	for (COLUMN column=1; column<=HORIZONTAL_DIM;column++)
            delete mPositions[row-1][column-1];
	row=static_cast<ROW>(static_cast<int>(row)+1);
    }
}

Position* Board::getThePosition(ROW row, COLUMN column)
{
/// for each Position (row,column), A <= row <= F , 1 <= column <= HORIZONTAL_DIM on the board, return the matching position

    Position posToBeChecked(row,column);
    if (posToBeChecked.Check())
        return mPositions[row-1][column-1];
    else
        return NULL;
}

void Board::PrintOn(ostream &out)
{
/// print the board on the stream out

    // first line with column names
    for (COLUMN column=1; column<=HORIZONTAL_DIM;column++)
        out << " |     " << column << "     ";
    out << " |"<< endl;
    // draw horizontal line
    out  << " "; // in non lines, there is a cipher

    for (COLUMN column=1; column<=HORIZONTAL_DIM;column++)
        out << "|------------";

    out << "|"<< endl;
    for (ROW row=A; row<=VERTICAL_DIM;)
    {
        out << static_cast<char>('A'+ static_cast<unsigned int>(row)-1);
        for (COLUMN column=1; column<=HORIZONTAL_DIM;column++)
        {
            // get token (if any) on currentPosition
	    	Position *currentPosition=mPositions[row-1][column-1];
            Token *currentToken=currentPosition->getToken();
            if (currentToken != NULL)
            {
                string currentColor=currentToken->getColor();
                string currentSideUp=(currentToken->isCROWN())? "(CROWN)" : "(PAWN) ";
 
                out << "|" << currentColor << currentSideUp ;

            }
            else
            {
                out   << "|            ";  // # of chars large enough for White(CROWN)
            }
        }
        row=static_cast<ROW>(static_cast<unsigned int>(row)+1);
        out << "|"<< endl;
        // draw horizontal line
        out  << " "; // in non lines, there is a cipher

        for (COLUMN column=1; column<=HORIZONTAL_DIM;column++)
            out << "|------------";
        out << "|"<< endl;
    }
    out << endl;
}




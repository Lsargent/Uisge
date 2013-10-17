#include "GlobalDefs.h"
#include <string>
using std::string;
#include "Board.h"
#include "Position.h"
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
	string columnHeader = " "; //initializes column header with a space
	string rowBorder = " "; //inits the row border
	string rowBorderElement = "|---------"; //inits the row border element
	for (COLUMN column=1; column <= HORIZONTAL_DIM; column++) //builds the rowBorder and column header because it does not change
	{
		string columnCenterSpacing = "    "; // Creates the space to center the the column label. Only works if the column label is one character
		columnHeader += ("|" + columnCenterSpacing + encodeColumn(column) + columnCenterSpacing); //Adds an element to the column header 
		rowBorder += rowBorderElement; //Adds a rowBorder element to build up the border row
	}
	columnHeader += "|\n"; //Adds the end to the column header
	rowBorder += "|\n"; //Adds the end to the row border 

	string boardContent=""; //The final board that will be printed
	string rowCenterElement = "|         "; //The element that represents the blank center of each board cell
	boardContent += columnHeader; //add the header to the board
	for (ROW row=A; row <= VERTICAL_DIM;) //Adds each row to the board
	{
		boardContent += rowBorder; //Adds the border of the row.
		boardContent += encodeRow(row); // Adds the name of the row
		for (int column=1; column <= HORIZONTAL_DIM; column++) // for each column add a row center element 
		{
			boardContent += rowCenterElement; //add a center element
		}
		boardContent += "|\n"; // Cap off the end of the row
		row=static_cast<ROW>(static_cast<int>(row)+1); //moves to next row
    }
	boardContent += rowBorder; // Capp of the end of the board with the bottom border

	out<<boardContent; //adds the boardCentent to the out stream
}




#include "GlobalDefs.h"
#include <stdlib.h>
#include <string>
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
	string columnHeader = " ";
	string rowBoarder = " ";
	string rowCenter = "";
	string rowBoarderElement = "|---------";
	string rowCenterElement = "|         ";
	string columnContent="";	
	for (int column=1; column <= HORIZONTAL_DIM; column++) 
	{
		string columnCenterSpacing = "    ";	
		columnHeader += ("|" + columnCenterSpacing + std::to_string(column) + columnCenterSpacing);
		rowBoarder += rowBoarderElement;
	}
	columnHeader += "|\n";
	rowBoarder += "|\n";

	for (ROW row=A; row <= VERTICAL_DIM;)
	{
		columnContent += rowBoarder;
		columnContent += rowNames[row-1];
		for (int column=1; column <= HORIZONTAL_DIM; column++) 
		{
			columnContent += rowCenterElement;
		}
		columnContent += "|\n";
		row=static_cast<ROW>(static_cast<int>(row)+1);
    }
	columnContent += rowBoarder;
	out<<columnHeader<<columnContent<<endl;
}




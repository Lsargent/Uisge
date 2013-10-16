/** @file Position.cpp
 */
#include "Position.h"
#include <iostream>

// Constructors & Destructor
Position::Position() : mRow(A), mColumn(0), mVacant(true)
{
}

Position::Position(ROW row, COLUMN column) : mRow(row), mColumn(column), mVacant(true)
{
}

Position::~Position(void)
{
}

// Public Methods

ROW Position::getRow() const
{
    return mRow;
}

void Position::setRow(ROW row)
{ 
    if (checkRow(row))
        mRow=row;
}
COLUMN Position::getColumn() const
{ 
    return mColumn;
}

void Position::setColumn(COLUMN column)
{
    if (checkColumn(column))
        mColumn=column;
}
bool Position::Check() const
{
    return checkRow(getRow()) && checkColumn(getColumn()) ;
}
bool Position::isVacant() const
{
    return mVacant;
}

bool Position::isOccupied() const
{
    return !isVacant();
}
void Position::setVacant()
{
    mVacant=true;
}
void Position::setOccupied()
{
    mVacant = false;
}

// Private Methods
bool Position::checkRow(ROW row) const
{
    return ( (A <=row) && (row <= F) );
}

bool Position::checkColumn(COLUMN column) const
{
    return ( (1 <= column) && (column <= HORIZONTAL_DIM) );
}



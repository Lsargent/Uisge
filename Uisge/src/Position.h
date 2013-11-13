/** @file Position.h
 */
#ifndef Position_H
#define Position_H

#include <stdlib.h>
#include <iostream>
using namespace std;

#include "GlobalDefs.h"

class Token;

/** @brief An object of this class represents a position on the board.
 *
 */
class Position
{
    ROW mRow;           ///< A <= mRow <= F
    COLUMN mColumn;     ///< 1 <= mColumn <= HORIZONTAL_DIM
    bool mVacant;       ///< Is position vacant, can be toggled.
    // References
    Token *mToken;      ///< The token that is connected to that position, if there is any! Might be NULL!
public:
    Position(); ///< Standard Constructor
    Position(ROW row, COLUMN column); ///< Constructor
    ~Position(void); ///< Destructor

    ROW getRow() const; ///< Gets the row of the position.
    void setRow(ROW row); ///< Sets the row of the position.

    COLUMN getColumn() const; ///< Gets the column of the position.
    void setColumn(COLUMN column); ///< Sets the column of the position.

    // Information
    bool Check() const;         ///< Checks, if position is within the boundaries of the board.
    bool isVacant() const;      ///< Is true, if there is no token connected with it.
    bool isOccupied() const;    ///< Is true, if there is a token on it.
    void setVacant();           ///< Sets the position to be vacant.
    void setOccupied();         ///< Sets the position to be occupied.

    Token *getToken() const; ///< Returns the token that is connected to that position, if there is any! Might be NULL!
    void connectTo(Token *token); ///< Connect a token to the current position.

    unsigned int getDistance(Position* ToPosition) const; ///< Examines the distance with the sum metrics and returns it.

    int getRowDifference(Position *thePosition) const;    ///< Examines the difference between rows.
    int getColumnDifference(Position *thePosition) const; ///< Examines the difference between columns.

    ADJACENCY getAdjacency(Position* thePosition) const; ///< Returns, if thePosition is adjacent to the current position, the adjacency direction (a geographic direction), toherwise NOT_ADJACENT
    bool isDiagonallyAdjacent(Position* thePosition) const; ///< Returns, whether thePosition is diagonally adjacent to the current position

private:
    bool checkRow(ROW row) const; ///< Checks, whether the row of the position is within the boundaries of the board.
    bool checkColumn(COLUMN column) const; ///< Checks, whether the column of the position is within the boundaries of the board.
};
#endif

/** @file Board.h
 */
#ifndef Board_H
#define Board_H

#include "GlobalDefs.h"
#include <iostream>
using namespace std;

class Position;

/** @brief An object of this class represents the board, it is a matrix of positions
 *  The board size is static: VERTICAL_DIM rows * HORIZONTAL_DIM columns.
 *  rows are A to F of enum type ROW
 *  columns are 1 to 7 of type COLUMN
 */

class Board
{
private:
    Position *mPositions[VERTICAL_DIM][HORIZONTAL_DIM]; ///< Each position is one of the "squares"
public:
    Board(void); ///< Constructor
    ~Board(void); ///< Destructor

    Position* getThePosition(ROW row, COLUMN column); ///< Pick a position by indexes, e.g. (D,4)

    void PrintOn(ostream &outStream); ///< Do an ASCII print of the board on stream outStream
};
#endif

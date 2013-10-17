#ifndef GlobalDefs_H
#define GlobalDefs_H

#include <string>
using std::string;
// for the board dimensions

const unsigned int VERTICAL_DIM = 6;    // A change here must be followed by changing encodeRow function, etROW and the  deCodeROW function
const unsigned int HORIZONTAL_DIM = 7;  // A change here must be followed by changing the deCodeCOLUMN function

enum etROW { A=1, B, C, D, E, F, INVALID_ROW }; // There are VERTICAL_DIM allowed rows
typedef enum etROW ROW;

typedef unsigned int COLUMN;

// Global Functions

// decodes a char into a valid ROW or into INVALID_ROW
ROW deCodeROW(char cSourceRow);

const unsigned int INVALID_COLUMN = HORIZONTAL_DIM + 1;
// decodes a char into a valid COLUMN or into INVALID_COLUMN
COLUMN deCodeCOLUMN(char cSourceColumn);

// encodes a ROW into a string
string encodeRow(ROW row);
// encodes a COLUMN into a string
string encodeColumn(COLUMN column);

#endif

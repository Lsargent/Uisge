/** @file GlobalDefs.cpp
 */
#include "GlobalDefs.h"

ROW deCodeROW(char cSourceRow)
{
    switch(cSourceRow)
    {
    case 'A': return A; break;
    case 'B': return B; break;
    case 'C': return C; break;
    case 'D': return D; break;
    case 'E': return E; break;
    case 'F': return F; break;
    default:  return INVALID_ROW; break;
    }
    // You should never get here
    return INVALID_ROW;
}

COLUMN deCodeCOLUMN(char cSourceColumn)
{
    switch(cSourceColumn)
    {
    case '1': return 1; break;
    case '2': return 2; break;
    case '3': return 3; break;
    case '4': return 4; break;
    case '5': return 5; break;
    case '6': return 6; break;
    case '7': return 7; break;
    default: return INVALID_COLUMN; break;
    }
    // You should never get here
    return INVALID_COLUMN;
}

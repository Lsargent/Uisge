/** @file Token.cpp
 */
#include "GlobalDefs.h"
#include "Game.h"
#include "Player.h"
#include "Team.h"
#include "Token.h"
#include "Position.h"
#include "Board.h"

#include <sstream>
#include <string>
using namespace std;

Token::Token(unsigned int nID, string aColor, SIDE_UP sideUp): 
    mID(nID),mColor(aColor), mSideUp(sideUp)
{
    mTeam=NULL;
}

Token::~Token(void)
{

}

unsigned int Token::getID() const
{
    return mID;
}


string Token::getColor() const
{
    return mColor;
}

string Token::getName() const // derived attribute
{
    // int -> string conversion for mID
    stringstream sstream;
    sstream << mID;

    return mColor + sstream.str();
}

bool Token::isPAWN() const
{
    return mSideUp == PAWN;
}

bool Token::isCROWN() const
{
    return mSideUp == CROWN;
}

void Token::putTo(Position *position)
{
    mPosition=position;
    position->connectTo(this);
    position->setOccupied();
}

void Token::leaveFrom(Position *position)
{
    position->connectTo(NULL);
    position->setVacant();
}

void Token::connectTo(Team *theTeam)
{
    mTeam=theTeam;
}

Team* Token::getTeam() const
{
    return mTeam;
}


bool Token::jump(Position *toPosition)
{
    // Navigating upwards to get the game
    Team *theTeam=getTeam();
    Player *thePlayer=theTeam->getPlayer();
    Game *theGame=thePlayer->getGame();

    /// \todo Jump only possible if there is a token between source and target position


    /// \todo put to toPosition

    /// \todo leave from current position

    
}

bool Token::isNeighbor(Token *theToken, ADJACENCY theDirection) const
{
    // is the token theToken a neighbor in the given direction?

    // Delegate it to the positions of the two tokens
    Position *myPosition=mPosition;
    Position *thePosition=theToken->mPosition;

    ADJACENCY kindOfAdjacency=myPosition->getAdjacency(thePosition);

    return kindOfAdjacency == theDirection ;
}

bool Token::isThereAHorizontalOrVerticalNeighborTokenInBetween(Position *thePosition) const
{
    ADJACENCY theDirection=NOT_ADJACENT;

    /// get theDirection by examining the differences in rows and in columns
    int rowDifference=mPosition->getRowDistance(thePosition);
    int columnDifference=mPosition->getColumnDistance(thePosition);

    if ((rowDifference == 0) && (columnDifference == -2))
        theDirection = EAST;

    if ((rowDifference == 0) && (columnDifference == 2))
        theDirection = WEST;

    if ((rowDifference == 2) && (columnDifference == 0))
        theDirection = NORTH;

    if ((rowDifference == -2) && (columnDifference == 0))
        theDirection = SOUTH;

    // Check if the intermediate position on theBoard is vacant
    ROW row=mPosition->getRow();
    COLUMN column=mPosition->getColumn();

    ROW rowOfIntermediatePosition;
    COLUMN columnOfIntermediatePosition;

    /// calculate the row and column of the intermediate position
    switch (theDirection)
    {
    case NORTH:
        rowOfIntermediatePosition=static_cast<ROW>(static_cast<unsigned int>(row)-1);
        columnOfIntermediatePosition=column;
        break;
    case EAST:
        rowOfIntermediatePosition=row;
        columnOfIntermediatePosition=column+1;
        break;
    case SOUTH:
        rowOfIntermediatePosition=static_cast<ROW>(static_cast<unsigned int>(row)+1);
        columnOfIntermediatePosition=column;
        break;
    case WEST:
        rowOfIntermediatePosition=row;
        columnOfIntermediatePosition=column-1;
        break;
    default:
        return false;
    }
    // Navigating upwards to get the board
    Team *theTeam=getTeam();
    Player *thePlayer=theTeam->getPlayer();
    Game *theGame=thePlayer->getGame();
    Board *theBoard=theGame->getTheBoard();

    Position *intermediatePosition=theBoard->getThePosition(rowOfIntermediatePosition, columnOfIntermediatePosition);

    if (intermediatePosition != NULL)
        return intermediatePosition->isOccupied(); // true: There is a token of the position to be jumped over
    else
        return false;  // not a correct Position, should never occur
}

void Token::turn()
{
    if (isPAWN())
		mSideUp=CROWN;
    else
		mSideUp=PAWN;

}

bool Token::draw(Position *toPosition)
{

    /// \todo do not turn stone

    /// \todo put to toPosition

    /// \todo leave from current position

    return true;
}

bool Token::move(Position *toPosition)
{
    // Navigating upwards to get the game
    Team *theTeam=getTeam();
    Player *thePlayer=theTeam->getPlayer();
    Game *theGame=thePlayer->getGame();

    // check if Position is not NULL
    if (toPosition == NULL)
    {
        theGame->setMessage("Target position is NULL. Try again.");
        return false;
    }

    /// \todo check if toPosition is on the board
    
    /// \todo check if position is occupied
    
    /// \todo decide whether it is a move or draw, and perform it

    /// \todo ...
    return true;
}


/** @file Token.cpp
 */
#include "GlobalDefs.h"
#include "Game.h"
#include "Player.h"
#include "Team.h"
#include "Token.h"
#include "Position.h"
#include "Board.h"
#include "Arrangement.h"

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

    // Jump only possible if there is a token between source and target position
    if (!(isThereAHorizontalOrVerticalNeighborTokenInBetween(toPosition)))
    {
        theGame->setMessage("You can only jump over another token. Try again.");
        return false;
    }

    // put to toPosition
	Position *currentPosition=this->mPosition;
    putTo(toPosition);
    // leave from current position
    
	//mPosition=toPosition;
    leaveFrom(currentPosition);

    // \todo Check is Arrangement is connected
	if(!theGame->getTheArrangement()->checkConnected())
	{
		return false;
		//putTo(currentPosition);
		//leaveFrom(toPosition);
	}
	else
	{
		return true;
	}
	//return 
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
    int rowDifference=mPosition->getRowDifference(thePosition);
    int columnDifference=mPosition->getColumnDifference(thePosition);

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

    // do not turn stone


    // put to toPosition
	Position *currentPosition=mPosition;
    putTo(toPosition);
    // leave from current position
    
	//mPosition=toPosition;
    leaveFrom(currentPosition);

    // \todo check connected
	Team *theTeam=getTeam();
	Player *thePlayer=theTeam->getPlayer();
	Game *theGame=thePlayer->getGame();


	if(!theGame->getTheArrangement()->checkConnected())
	{
		//putTo(currentPosition);
		//leaveFrom(toPosition);
	}
	else
	{
		return true;
	}
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

    // check if toPosition is on the board
    if ( !(toPosition->Check()))
    {
        theGame->setMessage("Target position is not on the board. Try again.");
        return false;
    }

    // check if position is occupied
    if (toPosition->isOccupied())
    {
        theGame->setMessage("Target position is occupied. Try again.");
        return false;
    }

    unsigned int theDistance=mPosition->getDistance(toPosition);
    switch (theDistance)
    {
    case 0:
        // toPosition is the same as starting position
        theGame->setMessage("Source and target are the same. Try again.");
        return true;
        break;
    case 1:
        // CROWN tokens can jump and draw, depending on the distance
        if (isCROWN())
        {
            return draw(toPosition);
        }
        else
        {
            theGame->setMessage("Only CROWN tokens can DRAW. Try again.");
            return false;
        }
        break;
    case 2:
        //either diagonally adjacent, or horizontallygetDistance/vertically two positions away
        if (mPosition->isDiagonallyAdjacent(toPosition))
        {
            if (isCROWN())
            {
                return draw(toPosition);
            }
        }
        else
        {
            {
                // not adjacent
                // CROWN and PAWN tokens can jump
                return jump(toPosition);
            }
        }
        break;
    default:
        // int -> string conversion for theDistance
        stringstream sstream;
        string sMessage="This token cannot move to a position with a distance of ";
        sstream << theDistance << ". Try again.";

        sMessage=sMessage + sstream.str();
        theGame->setMessage(sMessage);
        return false;
        break;
    }
    return true;
}


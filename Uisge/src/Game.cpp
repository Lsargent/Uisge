/** @file Game.cpp
 */
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

#include "GlobalDefs.h"

#include "Game.h"
#include "Player.h"
#include "Team.h"
#include "Token.h"
#include "Position.h"
#include "Board.h"
#include "Arrangement.h"


Game::Game(void)
{
    mName="Uisge";
    mFinished=false;
    mBoard= new Board;
    mMessage="Welcome to Uisge!";

    /// create the players and connect them to this game, White is the active player
    Player* thePlayer;

    thePlayer=new Player("White");
    mPlayers.push_back(thePlayer);
    thePlayer->connectTo(this);

    mActivePlayer=thePlayer;

    thePlayer=new Player("Black");
    mPlayers.push_back(thePlayer);
    thePlayer->connectTo(this);
	/// \todo create the arrangement 
	/// \todo add all players to it, collects all tokens

	mArrangement=new Arrangement();
	for (int i = 0; i < mPlayers.size(); i++)
	{
		mArrangement->Add(mPlayers[i]);
	}
    initialize();
}

Game::~Game(void)
{
    //free memory for allocated players, board and arrangement
    mPlayers.clear();
    delete mBoard;
    /// \todo handle arrangement
	delete(mArrangement);
}

void Game::setFinished()
{
    mFinished=true;
}

bool Game::isFinished()
{
    return mFinished;
}

Board* Game::getTheBoard() const
{
    return mBoard;
}

Player* Game::getThePlayer(string sName) const
{
/// get the player with name sName if possible, else return NULL
    for(unsigned int i=0 ; i < mPlayers.size() ; i++)
        if (mPlayers[i]->getName() == sName)
            return mPlayers[i];
    return NULL;
}
void Game::setActivePlayer(string sName)
{
    mActivePlayer=getThePlayer(sName);
}

Player* Game::getActivePlayer() const
{
    return mActivePlayer;
}

Arrangement* Game::getTheArrangement() const
{
/// \todo
	return mArrangement;
}

string Game::getMessage() const
{
    return mMessage;
}

void Game::setMessage(string theMessage)
{
    mMessage=theMessage;
}

void Game::initialize()
{
    Board  *theBoard=getTheBoard();

    // Player "White"
    Player *theWhitePlayer=getThePlayer("White");
    // Choose matching team
    Team   *theWhiteTeam=theWhitePlayer->getTheTeam();

    // handle first token of team "White"
    Token  *theToken=theWhiteTeam->getTheToken(1);
    Position *thePosition=theBoard->getThePosition(D,3);
    theToken->putTo(thePosition);

    // next token
    theToken=theWhiteTeam->getTheToken(2);
    thePosition=theBoard->getThePosition(D,4);
    theToken->putTo(thePosition);

    // next token
    theToken=theWhiteTeam->getTheToken(3);
    thePosition=theBoard->getThePosition(D,5);
    theToken->putTo(thePosition);

    // next token
    theToken=theWhiteTeam->getTheToken(4);
    thePosition=theBoard->getThePosition(D,6);
    theToken->putTo(thePosition);

    // next token
    theToken=theWhiteTeam->getTheToken(5);
    thePosition=theBoard->getThePosition(E,4);
    theToken->putTo(thePosition);

    // next token
    theToken=theWhiteTeam->getTheToken(6);
    thePosition=theBoard->getThePosition(E,5);
    theToken->putTo(thePosition);



    // Player "Black"
    Player *TheBlackPlayer=getThePlayer("Black");
    // choose matching team
    Team *theBlackTeam=TheBlackPlayer->getTheTeam();

    // handle first token of team "Black"
    theToken=theBlackTeam->getTheToken(1);
    thePosition=theBoard->getThePosition(B,3);
    theToken->putTo(thePosition);

    // next token
    theToken=theBlackTeam->getTheToken(2);
    thePosition=theBoard->getThePosition(B,4);
    theToken->putTo(thePosition);

    // next token
    theToken=theBlackTeam->getTheToken(3);
    thePosition=theBoard->getThePosition(C,2);
    theToken->putTo(thePosition);

    // next token
    theToken=theBlackTeam->getTheToken(4);
    thePosition=theBoard->getThePosition(C,3);
    theToken->putTo(thePosition);

    // next token
    theToken=theBlackTeam->getTheToken(5);
    thePosition=theBoard->getThePosition(C,4);
    theToken->putTo(thePosition);

    // next token
    theToken=theBlackTeam->getTheToken(6);
    thePosition=theBoard->getThePosition(C,5);
    theToken->putTo(thePosition);

}


void Game::run()
{
    // for getting input as single characters
    char cCmd;
    char cSourceRow;
    char cTargetRow;
    char cSourceColumn;
    char cTargetColumn;

    // store coordinates
    ROW SourceRow=INVALID_ROW;
    COLUMN SourceColumn=INVALID_COLUMN;

    ROW TargetRow=INVALID_ROW;
    COLUMN TargetColumn=INVALID_COLUMN;

    while (!(isFinished()))  // this loop control the input until the game is finished
    {
        bool continueLoop=false;

        continueLoop=UI(cout, cin,cCmd, cSourceRow, cSourceColumn, cTargetRow, cTargetColumn);

        if (continueLoop)
            continue;
        // check whether input is valid
        SourceRow=deCodeROW(cSourceRow);
        SourceColumn=deCodeCOLUMN(cSourceColumn);
        TargetRow=deCodeROW(cTargetRow);
        TargetColumn=deCodeCOLUMN(cTargetColumn);

        if ( (SourceRow    == INVALID_ROW)    ||
             (SourceColumn == INVALID_COLUMN) ||
             (TargetRow    == INVALID_ROW)    ||
             (TargetColumn == INVALID_COLUMN))
        {
            // nothing can be done here
            mMessage="Please choose a source position with a token on it and a target position that is free. Try again.";
            continue;
        }
		Board *theBoard=getTheBoard();
        Position *SourcePosition=theBoard->getThePosition(SourceRow,SourceColumn);
        Position *TargetPosition=theBoard->getThePosition(TargetRow,TargetColumn);

        Player *activePlayer=mActivePlayer;
        // Attempt to move from SourcePosition. The token there must belong to the team of the ActivePlayer
        // Check first if there is a token ...
        if (SourcePosition->isOccupied())
        {
            Player *selectedPlayer=SourcePosition->getToken()->getTeam()->getPlayer();
            if (activePlayer == selectedPlayer)
            {
                bool successfulMove=SourcePosition->getToken()->move(TargetPosition);
                // on successfulMove, change Players alternately
                if (successfulMove)
                {
                    // check if active player has won
                    string sPlayerName=activePlayer->getName();
					mMessage="Welcome to Uisge!";
                    if (activePlayer->hasWon())
                    {
                        stringstream sstream;
                        string sMessage="Player ";
                        sstream << sPlayerName << " wins the game!";

                        mMessage = sMessage + sstream.str();
                        setFinished();
                        cout << mMessage << endl;
                        continue; // the loop
                    }
                    if (sPlayerName == "White")
                        setActivePlayer("Black");
                    else
                        setActivePlayer("White");
                }
                else
                { // Move not possible, the reason is in mMessage
					//TargetPosition->getToken()->move(SourcePosition);
					mMessage="Please choose a qualified targetPosition." ;
                }
            }
            else // token is not of the active player
            {
                mMessage="Please choose a token of the active player. Try again." ;
            }
        }
        else // .. not occupied
        {
            mMessage="Please choose a source position with a token on it. Try again." ;
        }

    } // while
}

bool Game::UI(ostream& out, istream& in,
              char &cCmd,
              char &cSourceRow, char &cSourceColumn,
              char &cTargetRow, char &cTargetColumn)
{
    const char QUIT='q';
 
    Board *theBoard=getTheBoard();
    theBoard->PrintOn(out);
    out << "Message:" << mMessage << endl;
    out << "Active Player: " << mActivePlayer->getName() << endl;
    out << "Type" << endl;
    out << "'" << QUIT << "' for 'quit'" << endl;
    out << "or" << endl;
    out << "enter the coordinates for your move in the format" << endl;
    out << "Move:E 4 E 6" <<endl;
    out << "Move:";

    in  >> cCmd ;

    // if a command was given
    switch (cCmd)
    {
    case QUIT:
        setFinished();
        mMessage="Uisge is finished.";
        out << mMessage << endl;
        setFinished();
        return true; // continues the loop in run(), which will end then
        break;
    default:
        cSourceRow=cCmd; // non of the above commands was given, take it as first input for move
        break;
    }
    // no command given, read input
    in >> cSourceColumn >> cTargetRow >> cTargetColumn;

    return false; // no continue in the run() loop, run() body will be executed
}




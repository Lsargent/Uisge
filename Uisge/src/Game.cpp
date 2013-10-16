#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

#include "GlobalDefs.h"

#include "Game.h"
#include "Board.h"

Game::Game(void)
{
    mName="Uisge";
    mFinished=false;
    mBoard= new Board;



    initialize();
}

Game::~Game(void)
{
    // free memory for board
    delete mBoard;
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

    while (!(isFinished()))  // this loop controls the input until the game is finished
    {
        bool continueLoop=false;

        continueLoop=UI(cout, cin,cCmd, cSourceRow, cSourceColumn, cTargetRow, cTargetColumn);


        if (continueLoop)
            continue;


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
    // \todo: just for verification, the next line has to be thrown out later on
    out << "Command:" << "Entered Move:" << cSourceRow << " " << cSourceColumn << " " << cTargetRow << " " << cTargetColumn;

    return false; // no continue in the run() loop, run() body will be executed
}




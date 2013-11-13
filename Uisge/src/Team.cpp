/** @file Team.cpp
 */
#include "Team.h"
#include "Token.h"
#include "Player.h"

Team::Team(string sName)
{
 // for a team, create all tokens and connect them to the team
    mName=sName;
    for (unsigned int i=0; i < NO_OF_TOKENS; i++)
    {
        Token *theToken=new Token(i,mName,PAWN);
        theToken->connectTo(this);
        mTokens[i]=theToken;
    }
}

Team::~Team(void)
{
    for (unsigned int i=0; i < NO_OF_TOKENS; i++)
	delete mTokens[i];
}

bool Team::hasWon(void) const
{
// ask each token, if it has a CROWN on top of it
    bool Result = true;
    for (unsigned int i=0;  i < NO_OF_TOKENS; i++)
        Result = Result && mTokens[i]->isCROWN();
    return Result;
}

Token* Team::getTheToken(unsigned int i) const // counts from 1
{
    if ( (i >=1 ) && (i <= NO_OF_TOKENS ))
	return mTokens[i-1];
    else
        return NULL;
}

void Team::connectTo(Player *thePlayer)
{
    mPlayer=thePlayer;
}

Player* Team::getPlayer() const
{
    return mPlayer;
}

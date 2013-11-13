/** @file Player.cpp
 */
#include "Player.h"
#include "Game.h"
#include "Team.h"

Player::Player(string sName)
{
    mName=sName;
    mTeam=new Team(sName);
    mTeam->connectTo(this);
}

Player::~Player(void)
{
  delete mTeam;
}

string Player::getName() const
{
    return mName;
}

Team* Player::getTheTeam() const
{
    return mTeam;
}

Game* Player::getGame() const
{
    return mGame;
}

void Player::connectTo(Game *game)
{
    mGame=game;
}

bool Player::hasWon()
{
    return mTeam->hasWon();
}
bool Player::isActive()
{
    Game *theGame=getGame();
    Player *theActivePlayer=theGame->getActivePlayer();

    return (this == theActivePlayer);
}


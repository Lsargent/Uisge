#ifndef Team_H
#define Team_H

#include <stdlib.h>
#include <string>

using namespace std;


class Player;
class Token;

const unsigned int NO_OF_TOKENS=6;

/** @brief An object of this class represents a team, which ist a collection of all tokens of one player.
 *
 */
class Team
{
private:
    string mName; ///< The name of the team
    Token *mTokens[NO_OF_TOKENS]; ///< The collection of tokens, there are NO_OF_TOKENS per team.
    Player *mPlayer; ///< Pointer to the player the team belongs to.

public:
    Team(string sName); ///< Constructor
    ~Team(void); ///< Destructor


    bool hasWon() const; ///< Checks, if team has won.


    Token* getTheToken(unsigned int i) const;  ///< Get the i-th token of the team

    // for navigation
    void connectTo(Player *thePlayer); ///< Connects the player of that team.
    Player* getPlayer() const; ///< Returns the player that is connected to that team.
};

#endif

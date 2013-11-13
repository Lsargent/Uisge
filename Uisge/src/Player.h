/** @file Player.h
 */
#ifndef Player_H
#define Player_H

#include <string>
using namespace std;

class Game;
class Team;

/** @brief An object of this class represents a player.
 *
 */

class Player
{
private:
    unsigned int mID;  ///< A short id, for debug printing purposes
    string mName;      ///< A player are identified by mName, will be "White" or "Black"
    Team *mTeam;       ///< This is the team of the player.
    Game *mGame;       ///< This is the game the player belongs to.
public:

    Player(string cName); ///< Constructor
    ~Player(void); ///< Destructor

    // getters
    string getName() const; ///< Gets the name of the player.

    // Navigation
    Team* getTheTeam() const; ///< For navigation use. Get the team of the player
    Game* getGame() const;    ///< For navigation use. Get the game of the player

    void connectTo(Game *game);  ///< Build up reference to the game, which the player belongs to

    bool hasWon(); ///< Checks, whether player has won the game.


    bool isActive();  ///< Checks whether player is active

};

#endif

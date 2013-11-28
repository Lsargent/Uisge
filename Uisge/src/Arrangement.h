/** @file Arrangement.h
 */
#ifndef Arrangement_H
#define Arrangement_H

#include <vector>
#include <string>

class Player;
class Token;
class Team;

using namespace std;

/** @brief An object of this class represents the collection (vector) of all tokens on the board.
 * It can check whether all tokens are connected horizontally or vertically.
 * There is exactly one object of this class per game.
 *
 */

class Arrangement
{
private:
    bool mConnected; ///< Is true if connected
    vector<Token*> mTokens; ///< All tokens on the board
public:

    Arrangement(void); ///< Constructor
    ~Arrangement(void); ///< Destructor

    void Add(Player *player); ///< Add the Tokens of a player to the arrangement

    bool checkConnected() const;     ///< Check, whether all tokens are horizontally or vertically connected

};

#endif

/** @file Token.h
 */
#ifndef Token_H
#define Token_H

#include <string>
using namespace std;

#include "GlobalDefs.h"

enum etSIDE_UP { CROWN, PAWN };
typedef enum etSIDE_UP SIDE_UP;

class Position;
class Team;

/** @brief An object of this class represents a token.
 *
 */
class Token
{
private:
    unsigned int mID;
    string mColor;
    SIDE_UP mSideUp;
    Position *mPosition;
    Team *mTeam;
public:
    Token(unsigned int nID, string aColor, SIDE_UP sideUp);
    ~Token(void);
    //
    unsigned int getID() const;
    string getColor() const;
    string getName() const;

    bool isPAWN() const;   ///< Is PAWN side up?
    bool isCROWN() const;  ///< Is CROWN side up?

    /// The putTo and leaveFrom token help in moving a token
    void putTo(Position *position); ///< Puts token to position
    void leaveFrom(Position *position); ///< Token leaves position

    void connectTo(Team *team); ///< Connects token to a team.
    Team* getTeam() const; ///< Returns the team that is connected to that token.


    bool move(Position *toPosition); ///< perform move from mPosition to toPosition


    bool isNeighbor(Token *theToken, ADJACENCY theDirection) const; ///< Is the token theToken a neighbor in the direction theDirection?

    /// Get the information, whether there is a neighbor token in the given direction between the current token and theTargetPosition
    bool isThereAHorizontalOrVerticalNeighborTokenInBetween(Position *theTargetPosition) const;

private:
    void turn(); ///< PAWN turns into CROWN, CROWN turns into PAWN, when jumping.
    bool jump(Position *toPosition); ///< Perform jump.
    bool draw(Position *toPosition); ///< Perform draw.
};

#endif

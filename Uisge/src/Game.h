/** @file Game.h
 */
#ifndef Game_H
#define Game_H

#include <stdio.h>
#include <string>
using namespace std;

class Board;


/** @brief An object of this class represents the UISGE game.
 *
 */

class Game
{
private:
    string mName;  ///< Name of the game
    bool mFinished; ///< Is the game finished? Either stopped playing or one of the players won the game.
    Board *mBoard; ///< Pointer to the board
    string mMessage; ///< Info or error message (if an attempt is made, not to stick to the rules) to be shown on the UI

public:
    Game(void); ///< Constructor
    virtual ~Game(void); ///< Destructor


    void setFinished(); ///< One of the Players has won.
    bool isFinished();  ///< Check if game is finished

    /// Navigation
    Board* getTheBoard() const; ///< Only one board per game

    string getMessage() const;  ///< Sets message to be shown on the UI
    void setMessage(string theMessage); ///< Gets message to be shown on the UI

    void run(); ///< running a game means: loop {sending output, receiving input, checking input, perform desired action if possible}
    void initialize(); ///< puts the tokens to its start positions

    /// Shows the game information on the screen (out) and accepts input from keyboard (in).
    /// The input is stored in the char &cCmd, char &cSourceRow, char &cSourceColumn, char &cTargetRow, char &cTargetColumn
    bool UI(ostream& out, istream& in, char &cCmd, char &cSourceRow, char &cSourceColumn, char &cTargetRow, char &cTargetColumn);
};

#endif

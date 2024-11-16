#ifndef LAB7_GAME_H
#define LAB7_GAME_H

#include <vector>
#include <set>
#include <string>
#include "mahjong.h"
#include "brain.h"

using namespace std;

// Define the order for player by renaming bool type
typedef bool Turn;
#define PLAYER_1 false
#define PLAYER_2 true

// Struct that records the result of the game
struct Result {
    bool ifGameDraw = false;
    bool ifSelfDraw = false;
    int handScore = 0;
    Turn winner = PLAYER_1;
    unsigned tileLeft = 108;
};

// The class controlling the procedure of the game
class Game {

    // the tiles to be drawn
    vector<Tile> wall;

    // The hands of two players. 0 for your AI. 1 for the other.
    // We use a C++ container "multiset" (in library <set>) to store the hands,
    // which is very useful in our situation, you can look it up by yourself.
    // You may also use this container in your AI.

    multiset<Tile> hand[2];

    // the rivers (where the discarded tiles go) of two players. 0 for your AI. 1 for the other
    vector<Tile> river[2];

    // the pointer to the AIs. 0 for yours. 1 for the other
    Brain* pBrain[2]{};

    // the record the result of the game
    Result result;

    // deal initial 13-tile-hand to two players. Called only in Game constructor
    void initHand(Turn turn);

    // return the string plot of the game from a God's-eye view.
    // We use "string stream" and "lambda function" to implement the function,
    // which are useful in C++ coding (thought not required in this course).
    // You can look them up if you are interested.
    string plotGame();
public:

    // shuffle the tiles to the seed, store the AIs, deal initial hands
    Game(Brain* p1, Brain* p2, int seed);

    // progress the game by tail recursion. check "game.cpp" for detailed explanation
    void takeTurn(Turn turn);

    // get the result of the game
    Result getResult();
};

#include <iostream>

// We overload some operators for iostream to optimize the interaction.
// You can try to understand what they do by searching "overloading operators in C++" by yourself.
// If you are interested, you can try overloading an operator to plot "hands" in a more convenient manner.
// i.e. ostream &operator << (ostream &out, multiset<Tile> &hand);
istream &operator >> (istream &in, Suit &suit);
istream &operator >> (istream &in, Tile &tile);
ostream &operator << (ostream &out, Suit suit);
ostream &operator << (ostream &out, Tile tile);

#endif //LAB7_GAME_H

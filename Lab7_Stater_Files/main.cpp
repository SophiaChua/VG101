#include <iostream>
#include "game.h"
#include "brain.cpp"

using namespace std;

int main() {

    int seed;
    cin >> seed;

    MyBrain player1;
    SimpleBrain player2;

    Game game(&player1, &player2, seed);

    game.takeTurn(PLAYER_1);

    Result result = game.getResult();

    int roundScore = 2 * result.handScore + (int) result.tileLeft;

    cout << roundScore << endl;

    return 0;
}

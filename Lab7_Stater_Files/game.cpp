#include "game.h"
#include <algorithm>
#include <random>
#include <sstream>

using namespace std;

Game::Game(Brain* p1, Brain* p2, int seed): pBrain{p1, p2} {
    for (int suit = 0; suit < 3; ++suit)
        for (int ordinal = 1; ordinal <= 9; ++ordinal)
            for (int n = 0; n < 4; ++n)
                this->wall.emplace_back(ordinal, (Suit) suit);
    shuffle(this->wall.begin(), this->wall.end(), mt19937(seed));
    this->initHand(PLAYER_1);
    this->initHand(PLAYER_2);
}

void Game::initHand(Turn turn) {
    for (int i = 0; i < 13; ++i) {
        this->hand[turn].insert(this->wall.back());
        this->pBrain[turn]->getDraw(this->wall.back());
        this->wall.pop_back();
    }
}

void Game::takeTurn(Turn turn) {

    cout << this->plotGame();

    // Draw a tile from the wall.
    Tile tileDrawn = this->wall.back();
    this->wall.pop_back();

    // If the player can win by self draw with the tile,
    // ask the player for decision by calling the method "requestWin()".
    // If the player agree, record the game result, and RETURN.
    if (Hand(this->hand[turn], tileDrawn).getScore() != 0) {
        if (this->pBrain[turn]->requestWin(tileDrawn, true)) {
            this->result.ifGameDraw = false;
            this->result.ifSelfDraw = true;
            this->result.handScore = Hand(this->hand[turn], tileDrawn).getScore();
            this->result.winner = turn;
            this->result.tileLeft = this->wall.size();
            return;
        }
    }

    // Deal the tile to the player's hand,
    // and inform the player by calling the method "getDraw()"
    this->hand[turn].insert(tileDrawn);
    this->pBrain[turn]->getDraw(tileDrawn);

    // Request the player to discard a tile.
    // If the tile doesn't exist in the player's hand, discard the largest one.
    Tile tileToBeDiscarded = this->pBrain[turn]->requestDiscard();
    auto it = this->hand[turn].find(tileToBeDiscarded);
    if (it == this->hand[turn].end()) --it;
    Tile tileDiscarded = *it;
    this->hand[turn].erase(it);

    // If the opposite player can win by the discarded tile,
    // ask the opposite player for decision by calling the method "requestWin()".
    // If the opposite player agree, record the game result, and RETURN.
    if (Hand(this->hand[!turn], tileDiscarded).getScore() != 0) {
        if (this->pBrain[!turn]->requestWin(tileDiscarded, false)) {
            this->result.ifGameDraw = false;
            this->result.ifSelfDraw = false;
            this->result.handScore = Hand(this->hand[!turn], tileDiscarded).getScore();
            this->result.winner = !turn;
            this->result.tileLeft = this->wall.size();
            return;
        }
    }

    // Move the discarded tile to the player's river,
    // and inform the opposite player of the discard by calling the method "getOppDiscard()".
    this->river[turn].push_back(tileDiscarded);
    this->pBrain[!turn]->getOppDiscard(tileDiscarded);

    // If no tile remains in the wall, RETURN.
    if (this->wall.empty()) {
        this->result.ifGameDraw = true;
        this->result.tileLeft = 0;
        return;
    };

    // Switch the turn and continue the game by tail recursion.
    return this->takeTurn(!turn);
}

Result Game::getResult() {
    return result;
}

string Game::plotGame() {

    ostringstream ss;

    auto plotRiver = [&](int turn)-> void {
        int count = 0;
        for (auto tile : this->river[turn]) {
            ss << tile << ' ';
            if (++count % 14 == 0) ss << '|' << endl << "| ";
        }
        do ss << "   "; while (++count % 14 != 0);
    };

    auto plotHand = [&](int turn)-> void {
        for (auto it : this->hand[turn]) ss << it << ' ';
        for (int i = (int) this->hand[turn].size(); i < 14; ++i) ss << "   ";
    };

    ss << ' '; for (int i = 0; i < 43; ++i) ss << '_'; ss << ' ' << endl;
    ss << "/ "; plotHand(1); ss << '\\' << endl;
    ss << "| "; for (int i = 0; i < 21; ++i) ss << "- "; ss << '|' << endl;
    ss << "| "; plotRiver(1); ss << '|' << endl;
    ss << '|'; for (int i = 0; i < 43; ++i) ss << '-'; ss << '|' << endl;
    ss << "| "; plotRiver(0); ss << '|' << endl;
    ss << "| "; for (int i = 0; i < 21; ++i) ss << "- "; ss << '|' << endl;
    ss << "| "; plotHand(0); ss << '|' << endl;
    ss << '\\'; for (int i = 0; i < 43; ++i) ss << '_'; ss << '/' << endl;
    ss << endl;

    return ss.str();
    return "I hate drawing!\n";
}

istream &operator >> (istream &in, Suit &suit) {
    char ch;
    in >> ch;
    switch (ch) {
        default:
        case 'c': case 'C': suit = Character; break;
        case 'b': case 'B': suit = Bamboo; break;
        case 'd': case 'D': suit = Dot; break;
    }
    return in;
}

istream &operator >> (istream &in, Tile &tile) {
    char ch;
    in >> ch >> tile.suit;
    tile.ordinal = (ch >= '0' && ch <= '9') ? ch - '0' : 9;
    return in;
}

ostream &operator << (ostream &out, Suit suit) {
    switch (suit) {
        case Character: out << 'c'; break;
        case Bamboo: out << 'b'; break;
        case Dot: out << 'd'; break;
    }
    return out;
}

ostream &operator << (ostream &out, Tile tile) {
    out << tile.ordinal << tile.suit;
    return out;
}

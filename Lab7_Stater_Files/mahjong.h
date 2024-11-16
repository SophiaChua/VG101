#ifndef LAB7_MAHJONG_H
#define LAB7_MAHJONG_H

#include <set>

// Define Suit type.
enum Suit {
    Character, Bamboo, Dot
};

// Define Tile type
struct Tile {
    int ordinal{};
    Suit suit{};
    // The overloading of the operator "<" is essential for the type "multiset<Tile>".
    // Why? Look up by yourself.
    bool operator < (const Tile &tile) const {
        return this->suit < tile.suit || (this->suit == tile.suit && this->ordinal < tile.ordinal);
    }
    int toInt() const {return suit * 10 + ordinal;};
    explicit Tile(int i): ordinal(i % 10), suit((Suit)(i / 10)) {};
    Tile(int o, Suit s): ordinal(o), suit(s) {};
};

// Class designed for calculating the score of the hand.
// Because of the content conflict with Lab 6,
// "mahjong.cpp", which the class is implemented, is not available until Nov. 30.
// You can also use this in your brain by imitating how it is called in "game.cpp".
// e.g. int score = Hand(hand).getScore(), where "hand" is a multiset<Tile> type.
class Hand {
    int tiles[30]{};
    int* pScore = nullptr;
    int nSuit = 0, nQuad = 0, nMeld = 0, nPair = 0;
    bool All_Triplets = true, Eye_Triplets = true, Terminals_in_All_Sets = true;
    void search7Pairs() const;
    void dfs(int i);
    Hand* removePair(int i);
    Hand* removeTriplet(int i);
    Hand* removeSequence(int i);
    void dfs_checkOut() const;
public:
    explicit Hand(const std::multiset<Tile>& hand);
    explicit Hand(const std::multiset<Tile>& hand, Tile tile);
    int getScore();
};

#endif //LAB7_MAHJONG_H

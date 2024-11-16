#ifndef LAB7_BRAIN_H
#define LAB7_BRAIN_H

#include "mahjong.h"
#include <set>

using namespace std;

class Brain {
public:

    virtual void getDraw(Tile tileDrawn) = 0;

    virtual Tile requestDiscard() = 0;

    virtual void getOppDiscard(Tile tileDiscarded) = 0;

    virtual bool requestWin(Tile winningTile, bool isSelfDraw) = 0;

};

// A simple brain that discards the tile randomly and will never win.
class SimpleBrain : public Brain {
    multiset<Tile> hand;
public:
    void getDraw(Tile tile) override {
        hand.insert(tile);
    }

    void getOppDiscard(Tile tile) override {

    }

    Tile requestDiscard() override {
        int val = 0;
        for (auto tile : hand) val += tile.toInt() * tile.toInt();
        val %= 14;
        auto it = hand.begin();
        for (int i = 0; i < val; ++i) ++it;
        Tile tileToBeDiscarded = *it;
        hand.erase(it);
        return tileToBeDiscarded;
    }

    bool requestWin(Tile winningTile, bool isSelfDraw) override {

        return false;
    }
};


#endif //LAB7_BRAIN_H

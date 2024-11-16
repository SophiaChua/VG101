#include "brain.h"
#include "mahjong.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>

using namespace std;

/**
 * For this LAB, you only need to change this file.
 * You should write 4 functions defined in MyBrain class
 * Notice that MyBrain has no direct access to the Game.
 * BTW, the brain here (without changes) is just the "Straightforward AI" I mentioned in the lab description,
 * you can submit the this file without changes to JOJ can see what score it can get.
 */

// TODO: Create your data structure / class / functions here (optional)

class MyBrain : public Brain {

    // TODO: Create your class member here.
    multiset<Tile> hand;
    multiset<Tile> oppRiver;
    multiset<Tile> myRiver;

    void whichDiscardTile() {
        map<Tile, int> tile_count = map<Tile, int>(); 
        int count = 0; 
        int nPair = 0; 

        for (auto tile: hand) { 
            tile_count[tile]++;
        }

        for (auto it = tile_count.cbegin(); it != tile_count.cend(); ++it) {
            count = (*it).second; 

            if (nPair < 2 && count == 3) {
                tile_count[(*it).first] = count - 3;
            }
            //find the triplet, and decrease by 3
        }

        for (auto it = tile_count.cbegin(); it != tile_count.cend(); ++it) {
            //find the pair, and decrease by 2
            count = (*it).second; 

            if (nPair = 0 && count == 2){
                tile_count[(*it).first] = count - 2; 
                nPair++; 
            }
            if (count == 4){
                tile_count[(*it).first] = count - 4; 
            }
        }
    }

    /**
     * @brief this method will be called in Game when you draw a tile from the wall,
     * at the beginning of the game, you will draw 13 tiles as your initial hand
     * @param tileDrawn the tile you draw
     */
    void getDraw(Tile tileDrawn) override {

        // TODO: Complete this function
        hand.insert(tileDrawn);
    }

    /**
     * @brief this method will be called in Game when you should discard a tile
     * @return the tile you want to discard from your hand
     */
    Tile requestDiscard() override {

        // TODO: Complete this function

        int b = 0, c = 0, d = 0; 

        // int val = 0;
        for (auto tile : hand)                  //for each tile in hand do something to the tile
        {
            if (tile.suit == Character){
                c++;
            }
            else if (tile.suit == Bamboo){
                b++;
            }
            else if (tile.suit == Dot){
                d++; 
            }
        }

        cout << "c: " << c << ";b: " << b << ";d: " << d << endl;

        Suit suit_to_be_discarded;
        if (c < b && c < d && c!=0){
            suit_to_be_discarded = Character;
        }
        else if (b < d && b!=0){
            suit_to_be_discarded = Bamboo;
        }
        else {
            suit_to_be_discarded = Dot;
        }
        
        Tile tile_to_discard = Tile(1);
        for (auto tile : hand)
        {
            if (suit_to_be_discarded == tile.suit){
                tile_to_discard = tile;
                cout << "suit to discard: " << suit_to_be_discarded << endl; 
                cout << "tile to discard: " << tile << endl; 
            }
        }

        hand.erase(tile_to_discard);
        myRiver.insert(tile_to_discard); 
        return tile_to_discard;  

        // val %= 14;
        // auto it = hand.begin();
        // for (int i = 0; i < val; ++i) 
        //     ++it;
        // Tile tileToBeDiscarded = *it;
        // hand.erase(it);
        // return tileToBeDiscarded;

        // return {9, Dot};
    }

    /**
     * @brief this method will be called in Game when the other player discards a tile
     * @param tileDiscarded the tile discarded by the other player
     */
    void getOppDiscard(Tile tileDiscarded) override {

        // TODO: Complete this function
        oppRiver.insert(tileDiscarded); 
    }

    /**
     * @brief this method will be called in Game when you can claim for a winning
     * @param winningTile The tile that is going to make your hand a winning hand
     * @param isSelfDraw whether the type of winning is Self Draw
     * @return whether you agree to claim for a winning
     */
    bool requestWin(Tile winningTile, bool isSelfDraw) override {

        // TODO: Complete this function (or you can just leave it "return true")
        Hand cHand = Hand(hand);

        cout << "getScore: " << cHand.getScore() << endl; 

        if (cHand.getScore() > 0)
            return true;
        else 
            return false; 
    }

};


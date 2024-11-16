#include "brain.h"
#include "mahjong.h"
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
    map<int, int> tile_count = map<int, int>(); 
    Suit suit_to_discard; 
    int nMeld = 0, nPartner = 0, nPair = 0; 

    void tileToInt() {
        
        int c = 0, b = 0, d = 0; 

        for (auto tile : hand) {
            if (tile.suit == Character) {
                c++;
                tile_count[tile.ordinal]++; 
            }
            else if (tile.suit == Bamboo) {
                b++; 
                tile.ordinal += 10; 
                tile_count[tile.ordinal]++;
            }
            else if (tile.suit == Dot) {
                d++; 
                tile.ordinal += 20; 
                tile_count[tile.ordinal]++; 
            }
        }

        if (c < b && c < d && c != 0) {
            suit_to_discard = Character; 
        }   
        else if (b < d && b != 0) {
            suit_to_discard = Bamboo; 
        }
        else {
            suit_to_discard = Dot; 
        }
    }

    int distance(int i) {
        if (i == 30) {
            return 8 - 2 * nMeld - nPartner - nPair;  
        }
        else if (tile_count[i] == 0) {
            distance(i+1); 
        }
        else {
            if (nPair == 0 && tile_count[i] >= 2) {
                nPair++; 
                tile_count[i] -= 2; 
                distance(i); 
            }
            else if (tile_count[i] >= 3) {
                nMeld++; 
                tile_count[i] -= 3;
                distance(i);  
            }
            else if (i % 10 <= 7 && tile_count[i] >= 1 && tile_count[i+1] >= 1 && tile_count[i+2] >= 1) {
                nPartner++; 
                tile_count[i]--; 
                tile_count[i+1]--; 
                distance(i); 
            }
            else if (i % 10 <= 7 && tile_count[i] >= 1 && tile_count[i+2] >= 1) {
                nPartner++; 
                tile_count[i]--; 
                tile_count[i+1]--; 
                distance(i); 
            }
        }

        return 0; 
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
        int dVal = distance(1); 
        Tile tile_to_discard = Tile(1); 
        
        if (dVal != 0) {
            for (auto tile : hand) {
                if (tile.suit == suit_to_discard) {
                    tile_to_discard = tile; 
                    hand.erase(tile_to_discard);
                    return tile_to_discard;  
                }
            }
            
            for (int i = 0; i < 30; i++) {
                if (tile_count[i] == 1) {
                    // hand.erase(hand.find(1)); 
                }
            }
        }

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
        return true; 
    }

};
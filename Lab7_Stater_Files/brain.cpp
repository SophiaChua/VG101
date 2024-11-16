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
    map<Tile, int> river = map<Tile, int>(); 
    map<Tile, int> tile_count = map<Tile, int>(); 
    
    void countTiles() {
        // count and summarize all the tiles in hand
        tile_count.clear(); 
        for (auto tile : hand) {
            if (tile_count.count(tile) == 0)
                tile_count[tile] = 1;
            else
                tile_count[tile]++;
        }
    }

    void countTilesClean() {
        // clean up tile_count by removing all keys with value 0
        auto tile_count_it = tile_count.cbegin();
        while (tile_count_it != tile_count.cend()) {
            if (tile_count_it->second == 0) {
                tile_count.erase(tile_count_it++);
            }
            else {
                ++tile_count_it;
            }
        }
    }

    Suit whichDiscardSuit() {
        int b = 0, c = 0, d = 0; 

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

        Suit suit_to_be_discarded;
        if (c < b && c < d){
            suit_to_be_discarded = Character;
        }
        else if (b < d){
            suit_to_be_discarded = Bamboo;
        }
        else {
            suit_to_be_discarded = Dot;
        }

        return suit_to_be_discarded; 
    }

    Tile whichDiscardTile() {
        Suit suit_to_discard = whichDiscardSuit();
        for (auto tile : hand) {
            if (tile.suit == suit_to_discard) {
                return tile;
            }
        }

        countTiles();

        // //find sequence 
        // for (int isuit = 0; isuit < 3; isuit++) {
        //     for (int ord = 1; ord <= 7; ord++) {
        //         Suit suit = static_cast<Suit>(isuit);
        //         Tile tile1 = Tile(ord, suit);
        //         Tile tile2 = Tile(ord+1, suit);
        //         Tile tile3 = Tile(ord+2, suit);
        //         // if tile_count has tile1 and tile_count has tile2 and tile_count has tile3
        //         if (tile_count.count(tile1) > 1 && tile_count.count(tile2) > 1 && tile_count.count(tile3) > 1) {
        //             tile_count[tile1] -= 1; 
        //             tile_count[tile2] -= 1; 
        //             tile_count[tile3] -= 1; 

        //             // // std::cout << "Found sequence: " << tile1 << " " << tile2 << " " << tile3 << std::endl;
        //         }
        //     }
        // }

        //find the triplet, and decrease by 3
        Tile tile_to_discard = Tile(1);
        // vector<Tile> cleanup = vector<Tile>();
        // for (auto it = tile_count.begin(); it != tile_count.end(); ++it) {
        //     Tile tile = (*it).first;
        //     int count = (*it).second;

        //     if (count >= 3) {
        //         tile_count[tile] = count - 3;
        //         tile_to_discard = tile;

        //         // // std::cout << "Found triplet: " << tile << " " << tile << " " << tile << std::endl;
        //     }
        // }

        //find the pair, and decrease by 2
        for (auto it = tile_count.begin(); it != tile_count.end(); ++it) {
            Tile tile = (*it).first;
            int count = (*it).second;

            if (count >= 2) {
                tile_count[tile] = count - 2;
                tile_to_discard = tile;

                std::cout << "Found pair: " << tile << " " << tile << std::endl;
            }
        }

        //find consecutive tiles of the same suit 
        // for (int isuit = 0; isuit < 3; isuit++) {
        //     for (int ord = 1; ord <= 8; ord++) {
        //         Suit suit = static_cast<Suit>(isuit);
        //         Tile tile1 = Tile(ord, suit);
        //         Tile tile2 = Tile(ord+1, suit);
        //         // if tile_count has tile1 and tile_count has tile2 and tile_count has tile3
        //         if (tile_count.count(tile1) > 1 && tile_count.count(tile2) > 1) {
        //             tile_count[tile1] -= 1; 
        //             tile_count[tile2] -= 1;

        //             // // std::cout << "Found consecutive: " << tile1 << " " << tile2 << std::endl;
        //         }
        //     }
        // }

        countTilesClean();
        
        if (tile_count.size() > 0) {
            tile_to_discard = tile_count.cbegin()->first;
        }
        // select the tile with highest count in river
        int highest_river_count = 0;
        for (auto it : tile_count) {
            Tile tile = it.first;
            int count = it.second;
            auto river_it = river.find(tile);
            if (river_it != river.end()) {
                if (river_it->second > highest_river_count) {
                    tile_to_discard = tile;
                    highest_river_count = river_it->second;
                }
            }
        }

        return tile_to_discard;
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
        Tile tile_to_discard = whichDiscardTile();
        if (river.find(tile_to_discard) != river.end())
            river[tile_to_discard]++;
        else
            river[tile_to_discard] = 1;
        hand.erase(hand.find(tile_to_discard));
        cout << "Tile to discard: " << tile_to_discard << endl;
        return tile_to_discard; 
    }

    /**
     * @brief this method will be called in Game when the other player discards a tile
     * @param tileDiscarded the tile discarded by the other player
     */
    void getOppDiscard(Tile tileDiscarded) override {

        // TODO: Complete this function
        if (river.count(tileDiscarded) == 1)
            river[tileDiscarded]++;
        else
            river[tileDiscarded] = 1;
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
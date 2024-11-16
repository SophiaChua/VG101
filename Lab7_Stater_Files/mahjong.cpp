#include "mahjong.h"

Hand::Hand(const std::multiset<Tile> & hand, Tile tile_) {
    this->tiles[tile_.toInt()]++;
    for (Tile const & tile : hand) {
        this->tiles[tile.toInt()]++;
    }
}

Hand::Hand(const std::multiset<Tile> & hand) {
    for (Tile const & tile : hand) {
        this->tiles[tile.toInt()]++;
    }
}

int Hand::getScore() {
    for (int suit = 0; suit < 3; ++suit) {
        bool ifSuitExist = false;
        for (int ordinal = 1; ordinal <= 9; ++ordinal) {
            if (this->tiles[10 * suit + ordinal] > 0) {
                ifSuitExist = true;
            }
        }
        if (ifSuitExist) {
            this->nSuit++;
        }
    }
    if (this->nSuit == 3) {
        return 0;
    }
    for (int const & tile : this->tiles) {
        if (tile == 4) {
            this->nQuad++;
        }
    }
    int score = 0;
    this->pScore = &score;
    this->search7Pairs();
    this->dfs(1);
    return score;
}

void Hand::search7Pairs() const{
    int numOfPair = 0;
    for (int const & tile : this->tiles) {
        if (tile == 2) {
            numOfPair++;
        }
        else if (tile == 4) {
            numOfPair += 2;
        }
    }
    if (numOfPair == 7) {
        int tempScore = 4;
        if (this->nSuit == 1) {
            tempScore *= 4;
        }
        for (int i = 0; i < this->nQuad; ++i) {
            tempScore *= 2;
        }
        if (*this->pScore < tempScore) {
            *this->pScore = tempScore;
        }
    }
}

void Hand::dfs(int i) {
    if (i == 30) {
        this->dfs_checkOut();
    }
    else if (this->tiles[i] == 0) {
        this->dfs(i + 1);
    }
    else {
        if (this->nPair == 0 && this->tiles[i] >= 2) {
            Hand(*this).removePair(i)->dfs(i);
        }
        if (this->tiles[i] >= 3) {
            Hand(*this).removeTriplet(i)->dfs(i);
        }
        if (i % 10 <= 7 && this->tiles[i] >= 1 && this->tiles[i+1] >= 1 && this->tiles[i+2] >= 1) {
            Hand(*this).removeSequence(i)->dfs(i);
        }
    }
}

Hand *Hand::removePair(int i) {
    this->tiles[i] -= 2;
    this->nPair++;
    if (i % 10 != 1 && i % 10 != 9) {
        this->Terminals_in_All_Sets = false;
    }
    if (i % 10 != 2 && i % 10 != 5 && i % 10 != 8) {
        this->Eye_Triplets = false;
    }
    return this;
}

Hand *Hand::removeTriplet(int i) {
    this->tiles[i] -= 3;
    this->nMeld++;
    if (i % 10 != 1 && i % 10 != 9) {
        this->Terminals_in_All_Sets = false;
    }
    if (i % 10 != 2 && i % 10 != 5 && i % 10 != 8) {
        this->Eye_Triplets = false;
    }
    return this;
}

Hand *Hand::removeSequence(int i) {
    this->tiles[i]--;
    this->tiles[i + 1]--;
    this->tiles[i + 2]--;
    this->nMeld++;
    this->All_Triplets = false;
    this->Eye_Triplets = false;
    if (i % 10 != 1 && i % 10 != 7) {
        this->Terminals_in_All_Sets = false;
    }
    return this;
}

void Hand::dfs_checkOut() const {
    if (this->nMeld == 4 && this->nPair == 1) {
        int tempScore = 1;
        if (this->Eye_Triplets == 1) {
            tempScore = 8;
        }
        else if (this->Terminals_in_All_Sets == 1) {
            tempScore = 4;
        }
        else if (this->All_Triplets == 1) {
            tempScore = 2;
        }
        if (this->nSuit == 1) {
            tempScore *= 4;
        }
        for (int i = 0; i < this->nQuad; ++i) {
            tempScore *= 2;
        }
        if (*this->pScore < tempScore) {
            *this->pScore = tempScore;
        }
    }
}

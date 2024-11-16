typedef struct {
    int tiles[30];
    int* pScore;
    int nSuit, nQuad, nMeld, nPair;
    int All_Triplets, Eye_Triplets, Terminals_in_All_Sets;
} Hand;

void search7Pairs(const Hand* pHand);
void dfs(const Hand* pHand, int i);
void removePair(Hand* pHand, int i);
void removeTriplet(Hand* pHand, int i);
void removeSequence(Hand* pHand, int i);
void dfs_checkOut(const Hand* pHand);

int getScore(const char strHand[]) {
    Hand hand = {{0}, 0, 0, 0, 0, 0, 1, 1, 1};
    const char* p = strHand;
    while (*(++p) != '\0');
    int adder = 0;
    while (p-- != strHand) {
        if (*p < '0' || *p > '9') {
            if (*p == 'c') adder = 0;
            if (*p == 'b') adder = 10;
            if (*p == 'd') adder = 20;
        } else hand.tiles[*p - '0' + adder]++;
    }

    for (int suit = 0; suit < 3; ++suit) {
        int ifSuitExist = 0;
        for (int ordinal = 1; ordinal <= 9; ++ordinal) {
            if (hand.tiles[10 * suit + ordinal] > 0) {
                ifSuitExist = 1;
            }
        }
        if (ifSuitExist == 1) {
            hand.nSuit++;
        }
    }
    if (hand.nSuit == 3) {
        return 0;
    }
    for (int i = 1; i < 30; ++i) {
        if (hand.tiles[i] == 4) {
            hand.nQuad++;
        }
    }

    int score = 0;
    hand.pScore = &score;
    search7Pairs(&hand);
    dfs(&hand, 1);
    return score;
}

void search7Pairs(const Hand* pHand) {
    int numOfPair = 0;
    for (int i = 1; i < 30; ++i) {
        if (pHand->tiles[i] == 2) {
            numOfPair++;
        }
        else if (pHand->tiles[i] == 4) {
            numOfPair += 2;
        }
    }
    if (numOfPair == 7) {
        int tempScore = 4;
        if (pHand->nSuit == 1) {
            tempScore *= 4;
        }
        for (int i = 0; i < pHand->nQuad; ++i) {
            tempScore *= 2;
        }
        if (*pHand->pScore < tempScore) {
            *pHand->pScore = tempScore;
        }
    }
}

void dfs(const Hand* pHand, int i) {
    if (i == 30) {
        dfs_checkOut(pHand);
    }
    else if (pHand->tiles[i] == 0) {
        dfs(pHand, i + 1);
    }
    else {
        if (pHand->nPair == 0 && pHand->tiles[i] >= 2) {
            Hand hand = *pHand;
            removePair(&hand, i);
            dfs(&hand, i);
        }
        if (pHand->tiles[i] >= 3) {
            Hand newHand = *pHand;
            removeTriplet(&newHand, i);
            dfs(&newHand, i);
        }
        if (i % 10 <= 7 && pHand->tiles[i] >= 1 && pHand->tiles[i + 1] >= 1 && pHand->tiles[i + 2] >= 1) {
            Hand newHand = *pHand;
            removeSequence(&newHand, i);
            dfs(&newHand, i);
        }
    }
}

void removePair(Hand* pHand, int i) {
    pHand->tiles[i] -= 2;
    pHand->nPair++;
    if (i % 10 != 1 && i % 10 != 9) {
        pHand->Terminals_in_All_Sets = 0;
    }
    if (i % 10 != 2 && i % 10 != 5 && i % 10 != 8) {
        pHand->Eye_Triplets = 0;
    }
}

void removeTriplet(Hand* pHand, int i) {
    pHand->tiles[i] -= 3;
    pHand->nMeld++;
    if (i % 10 != 1 && i % 10 != 9) {
        pHand->Terminals_in_All_Sets = 0;
    }
    if (i % 10 != 2 && i % 10 != 5 && i % 10 != 8) {
        pHand->Eye_Triplets = 0;
    }
}

void removeSequence(Hand* pHand, int i) {
    pHand->tiles[i]--; pHand->tiles[i + 1]--; pHand->tiles[i + 2]--;
    pHand->nMeld++;
    pHand->All_Triplets = 0;
    pHand->Eye_Triplets = 0;
    if (i % 10 != 1 && i % 10 != 7) {
        pHand->Terminals_in_All_Sets = 0;
    }
}

void dfs_checkOut(const Hand* pHand) {
    if (pHand->nMeld == 4 && pHand->nPair == 1) {
        int tempScore = 1;
        if (pHand->Eye_Triplets == 1) {
            tempScore = 8;
        }
        else if (pHand->Terminals_in_All_Sets == 1) {
            tempScore = 4;
        }
        else if (pHand->All_Triplets == 1) {
            tempScore = 2;
        }
        if (pHand->nSuit == 1) {
            tempScore *= 4;
        }
        for (int i = 0; i < pHand->nQuad; ++i) {
            tempScore *= 2;
        }
        if (*pHand->pScore < tempScore) {
            *pHand->pScore = tempScore;
        }
    }
}

#include <stdio.h>
#include <string.h>

#define LENGTH 14 

typedef struct{
    char suit; 
    int rank; 
} hand; 

void store (const char strHand[], hand tile[14])
{
    char temp; 
    int n = 0; 

    for (int i = strlen(strHand) - 1; i >= 0; i--)
    {
        if (strHand[i] > 'a')
        {
            temp = strHand[i];
        }
        else 
        {
            tile[n].suit = temp; 
            tile[n].rank = strHand[i] - '0'; 
            n++;
        }
    }
}

int sort (hand tile[14], int length)
{
    int breakpoint; 
    int temp; 

    //find where it switches to a different suit. 
    for (int i = 0; i < length - 1; i++)
    {
        if (tile[i].suit != tile[i+1].suit)
        {
            breakpoint = i + 1; 
            break; 
        }
        else 
        {
            breakpoint = 14; 
        }
    }

    for (int i = 0; i < breakpoint - 1; i++)
    {
        for (int j = 0; j < breakpoint - i - 1; j++)
        {
            if (tile[j].rank > tile[j+1].rank)
            {
                temp = tile[j].rank; 
                tile[j].rank = tile[j+1].rank; 
                tile[j+1].rank = temp; 
            }
        }
    }

    for (int i = breakpoint; i < length - 1; i++)
    {
        for (int j = breakpoint; j < length - i % breakpoint - 1; j++)
        {
            if (tile[j].rank > tile[j+1].rank)
            {
                temp = tile[j].rank; 
                tile[j].rank = tile[j+1].rank; 
                tile[j+1].rank = temp; 
            }
        }
    }

    return breakpoint; 
}

int AllPairs (hand tile[14], int breakpoint)
{
    int count = 0; 

    if (breakpoint % 2 == 1)
        return 0; 
    else 
    {
        for (int i = 0; i < LENGTH/2; i++)
        {
            if (tile[2*i].rank == tile[2*i+1].rank)
            {
                count++; 
            }
        }

        if (count == 7)
            return 4; 
        else
            return 0; 
    }
}

int Triplets (hand tile[14])
{
    int TriCount = 0;  

    for (int i = 0; i < 4; i++)
    {
        if (tile[3*i].rank == tile[3*i+1].rank && tile[3*i].rank == tile[3*i+2].rank)
            TriCount++; 
    }

    if (TriCount == 4)
        return 2; 
    else 
        return 0; 
}

//A mix between triplets and sequences
int Melds (hand tile [14], int arr[4][4])
{
    int r, c; 

    for (int i = 0; i < 12; i++)
    {
        r = 0;  

        while (1)
        {
            if (r == 4)
                return 0; 
            else if (arr[r][0] == 0)
            {
                arr[r][0] = tile[i].suit;
                arr[r][1] = tile[i].rank; 
                break; 
            }
            else if (arr[r][0] != tile[i].suit)
                r++; 
            else if (arr[r][2] == 0)
            {
                if (arr[r][1] == tile[i].rank && arr[r][1] == tile[i+1].rank)
                {
                    arr[r][2] = tile[i].rank;
                    break; 
                } 
                else if (arr[r][1] == tile[i].rank - 1)
                {
                    arr[r][2] = tile[i].rank; 
                    break; 
                }
                else
                    r++; 
            } 
            else if (arr[r][3] != 0)
                r++; 
            else
            {
                if (arr[r][1] == arr[r][2] && arr[r][1] == tile[i].rank)
                {
                    arr[r][3] == tile[i].rank; 
                    break; 
                }
                else if (arr[r][1] == arr[r][2] - 1 && arr[r][1] == tile[i].rank - 2)
                {
                    arr[r][3] == tile[i].rank; 
                    break; 
                }
                else 
                    r++; 
            }
        }
    }

    return 1; 
}

int Terminals (hand tile[14], int arr[4][4])
{
    int TerminalCount = 0, n = 0, flag = 0;
    hand temp[14];  
    
    for (int i = 0; i < LENGTH; i++)
    {
        temp[i].suit = 'a'; 
        temp[i].rank = 0; 
    }

    //to account for the pair 
    if (tile[12].rank == 1 || tile[12].rank == 9)
        flag = 1; 

    //check if there is a terminal in each triplet 
    for (int i = 0; i < 4; i++)
    {
        if (arr[i][1] == 1 || arr[i][1] == 9 || arr[i][2] == 1 || arr[i][2] == 9 || arr[i][3] == 1 || arr[i][3] == 9)
            TerminalCount++; 
    }

    //store pure triplets
    for (int i = 0; i < 4; i++)
    {
        if (arr[i][1] == arr[i][2] && arr[i][1] == arr[i][3])
        {
            temp[n].suit = arr[i][0]; 
            temp[n].rank = arr[i][1]; 
            n++; 
        }
    }
    
    int slice = sort(temp, 5); 

    int Count = 0; 

    //check if the pure triplets contain terminals (after they have been stored) 
    for (int i = 0; i < 4; i++)
    {
        if (temp[i].rank == 1 || temp[i].rank == 9)
            Count++; 
    }

    int bool = 0; 
    
    if (n == 3) //3 Pure Triplet Sets
    {
        if (temp[0].rank == temp[1].rank - 1 && temp[0].rank == temp[2].rank - 2) //check if the triplets can form a sequence as well
            bool = 1; 
        else 
            bool = 0; 
    }
    else if (n == 4); // 4 Pure Triplet Sets
    {
        if (slice == 1) // 1st Triplet is a different suit, the other 3 are in the same suit 
        {
            if (temp[1].rank == temp[2].rank - 1 && temp[1].rank == temp[3].rank - 2) // check if they can form a sequence instead
                bool = 1; 
            else 
                bool = 0; 
        }
        
        if (slice == 3) // the first 3 triplets are in the same suit, the last one is in a different suit
        {
            if (temp[0].rank == temp[1].rank - 1 && temp[0].rank == temp[2].rank - 2)
                bool = 1; 
            else 
                bool = 0; 
        }

        if (slice == 4) // all the triplets belong to the same suit 
        {
            if (temp[0].rank == temp[1].rank - 1 && temp[0].rank == temp[2].rank - 2)
            {
                if (temp[0].rank == 1 || temp[2].rank == 9)
                    bool = 1; 
                else
                    bool = 0; 
            }
            else if (temp[1].rank == temp[2].rank - 1 && temp[1].rank == temp[3].rank - 2)
            {
                if (temp[1].rank == 1 || temp[3].rank == 9)
                    bool = 1; 
                else 
                    bool = 0; 
            }
            else 
                bool = 0; 
        }
    }

    if (flag == 0) // the pair does not contain a terminal 
        return 0; 
    else if (TerminalCount == 4) // all triplets contain a terminal 
        return 1; 
    else if (TerminalCount < 2) 
        return 0; 
    else if (n < 3) // less than 3 triplet sets
        return 0; 
    else if (n == 3) // 3 triplet sets 
    {
        if (Count == TerminalCount) // if stored (simplified/to account for sequences) triplet's contain the same number of terminals as the original (not stored) ones
            return 0; 
        else if (slice == 3)
            return bool; 
        else 
            return 0; 
    }
    else if (n == 4) // 4 triplet sets 
    {
        if (slice == 4) 
            return bool; 
        if (slice == 2) // not possible because we need 3 triplet sets of the same suit to form one sequence 
            return 0; 
        if (slice == 1)
        {
            if (temp[0].rank == 1 || temp[0].rank == 9) // check if the first triplet also contains a terminal 
                return bool; // check if the other 3 triplets contain a terminal 
            else 
                return 0;  
        }
        if (slice == 3)
        {
            if (temp[3].rank == 1 || temp[3].rank == 9) // check if the last triplet also contains a terminal 
                return bool; // check if the other 3 triplets contain a terminal 
            else 
                return 0; 
        }
    }

    return 0; 
}

int _258Triplets (hand tile[14])
{
    int SpecialCount = 0; 

    for (int i = 0; i < LENGTH; i++)
    {
        if (tile[i].rank == 2 || tile[i].rank == 5 || tile[i].rank == 8)
            SpecialCount++; 
    }

    if (SpecialCount == 14)
        return 8; 
    else 
        return 0; 
}

int isFullFlush (int breakpoint)
{
    if (breakpoint = 14)
        return 4; 
    else 
        return 1; 
}

int Bonus (hand tile[14], int breakpoint)
{
    int RootCount = 1; 

    for (int i = 0; i < breakpoint - 3; i++)
    {
        if (tile[i].rank == tile[i+1].rank && tile[i].rank == tile[i+2].rank && tile[i].rank == tile[i+3].rank)
        {
            RootCount *= 2; 
        }
    }

    for (int i = breakpoint; i < LENGTH - 3; i++)
    {
        if (tile[i].rank == tile[i+1].rank && tile[i].rank == tile[i+2].rank && tile[i].rank == tile[i+3].rank)
        {
            RootCount *= 2; 
        }
    }

    return RootCount; 
}

int getScore (const char strHand[])
{
    hand tile[14]; 

    store(strHand, tile);
    int breakpoint = sort(tile, LENGTH);  
    
    //bonus 
    int FlushBonus = isFullFlush(breakpoint); 
    int RootBonus = Bonus(tile, breakpoint);  

    //pattern checking 
    int isAllPairs = AllPairs(tile, breakpoint);
    if (isAllPairs == 4)
        return isAllPairs * FlushBonus * RootBonus;

    if (_258Triplets(tile) != 0)
        return _258Triplets(tile); 

    //isolate the pair 
    int start, stop, flag2, flag3; 
    hand temp; 
    int arr[4][4] = {0}; 

    if (breakpoint % 3 == 2)
    {
        start = 0; 
        stop = breakpoint - 1; 
    }
    else if (breakpoint % 3 == 0)
    {
        start = breakpoint; 
        stop = LENGTH - 1; 
    }
    else 
        return 0; //not a winning hand

    for (int i = start; i < stop; i++)
    {
        sort(tile, LENGTH); 

        if (tile[i].rank == tile[i+1].rank)
        {
            temp.rank = tile[i+1].rank;
            temp.suit = tile[i+1].suit; 
            tile[i+1].rank = tile[13].rank;
            tile[i+1].suit = tile[13].suit; 
            tile[13].rank = temp.rank; 
            tile[13].suit = temp.suit;  

            temp.rank = tile[i].rank;
            temp.suit = tile[i].suit; 
            tile[i].rank = tile[12].rank;
            tile[i].suit = tile[12].suit; 
            tile[12].rank = temp.rank; 
            tile[12].suit = temp.suit;  

            sort(tile, 12);
            
            // Triplets or Sequence (which gives more points)
            int m = Melds(tile, arr); 
            if (m == 0)
                return 0; // more than 4 triplets (impossible)

            int t = Terminals(tile, arr); 
            if (t == 1)
                return 4 * FlushBonus * RootBonus; 

            int tri = Triplets(tile); 
                if (tri == 2)
                    return 2 * FlushBonus * RootBonus; 
                else 
                    return 1 * FlushBonus * RootBonus; 
        }
    }
}

int main() {
    char patternName[10][30] = {
            "Chicken Hand",
            "Full Flush",
            "All Triplets",
            "Pure Triplets",
            "2/5/8 Triplets",
            "Terminals in All Sets",
            "Pure Terminals in All Sets",
            "Seven Pairs",
            "Pure Seven Pairs",
            "Not Winning"
    };

    int secCount[10] = {0};
    int secWA[10] = {0};
    int WA = 0;
    int hitWin = 0;
    int hitLose = 0;

    for (int i = 0; i < 10;) {
        char strHand[30];
        int score;
        scanf("%s", strHand);
        if (*strHand == 'n') {
            i++; continue;
        }
        secCount[i]++;
        scanf("%d", &score);
        int testScore = -1;
        testScore = getScore(strHand);
        if (testScore != score) {
            if (WA == 0) {
                printf("The following is some testcase you fail\n");
                printf("strHand - Expected Answer -  Your Answer\n");
            }
            secWA[i]++;
            WA++;
            if (secWA[i] <= 1) {
                printf("%-28s  %-3d  %d\n", strHand, score, testScore);
            }
        }
        if (testScore > 0 && score > 0) hitWin++;
        else if (testScore == 0 && score == 0) hitLose++;
    }

    if (WA == 0) {
        printf("Congratulation! You pass all the testcase.\n");
    }
    printf("\n");
    for (int i = 0; i < 10; ++i) {
        printf("%-27s[%6.2f%%]\n", patternName[i], (double) (secCount[i] - secWA[i]) / secCount[i] * 100);
    }
    printf("\n");
    double hitRate = (double) hitWin / 26000 / 2 + (double) hitLose / 4000 / 2;
    printf("Determine Winning or Not   [%6.2f%%]\n", hitRate * 100);
    printf("\n");

    int score = 0;
    for (int i = 0; i < 10; ++i) {
        int ps = (secCount[i] - secWA[i]) * 100 / secCount[i];
        if (ps > 95) score += ps - 95;
    }
    int lowerBound = (30000 - WA) * 100 / 30000;
    if (lowerBound >= 90) score += 90;
    else score += lowerBound;
    score -= 35;
    int hitBound = (int) (140 * (hitRate - 0.5 > 0 ? hitRate - 0.5 : 0));
    if (score < hitBound) score = hitBound;
    else if (score > hitBound + 35) score = hitBound + 35;

    printf("Total Score: %d", score);
    return 0;
}



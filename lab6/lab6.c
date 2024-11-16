#include <stdio.h>
#include <string.h>

struct tile{
    char suit;
    int rank;
};

void store (const char strHand[], struct tile hand[14]){
    char temp;
    int n = 0, i = strlen(strHand) - 1;
	
    while (n < 14){
        if (strHand[i] >= 'a'){
            temp = strHand[i--];
        }
        else{
            hand[n].suit = temp;
            hand[n].rank = strHand[i] - '0';
            n++;
            i--;
        }
    }
}

int sort (struct tile hand[14], int length){
    int trigger = 1, breakpoint = 0;
    struct tile temp;
	
    while (trigger == 1){
        trigger = 0;
        for (int i = 0; i < length - 1; i++){
                if (hand[i].suit > hand[i+1].suit){
                temp.suit = hand[i].suit;
                temp.rank = hand[i].rank;
                hand[i].suit = hand[i+1].suit;
                hand[i].rank = hand[i+1].rank;
                hand[i+1].suit = temp.suit;
                hand[i+1].rank = temp.rank;
                trigger = 1;
            }
        }
    }

    for (int i = 0; i < length - 1; i++){
        if (hand[i].suit != hand[i+1].suit){
            breakpoint = i+1;
            break;
        }
    }
	
    trigger = 1;
    while (trigger == 1){
        trigger = 0;
        for (int i = 0; i < breakpoint - 1; i++){
            if (hand[i].rank > hand[i+1].rank){
                temp.rank = hand[i].rank;
                hand[i].rank = hand[i+1].rank;
                hand[i+1].rank = temp.rank;
                trigger = 1;
            }
        }
    }
	
    trigger = 1;
    while (trigger == 1){
        trigger = 0;
        for (int i = breakpoint; i < length - 1; i++){
            if (hand[i].rank > hand[i+1].rank){
                temp.rank = hand[i].rank;
                hand[i].rank = hand[i+1].rank;
                hand[i+1].rank = temp.rank;
                trigger = 1;
            }
        }
    }
	
    return breakpoint;
}

int AllPairs (struct tile hand[14], int breakpoint){ 
    int PairCount = 0; 

    if (breakpoint % 2 == 1){
        return 0;
    }
    else{
        for (int i = 0; i < 7; i++){
            if (hand[2*i].rank == hand[2*i+1].rank){
                PairCount++;
            }
        }

        if (PairCount == 7){
            return 1;
        }
        else{
            return 0;
        }
    }
}

int Triplets (struct tile hand[14]){ 
    int TriCount = 0; 
    
    for (int i = 0; i < 4; i++){
        if (hand[3*i].rank == hand[3*i+1].rank && hand[3*i].rank == hand[3*i+2].rank){
            TriCount++;
        }
    }
    
    if (TriCount == 4){
        return 1;
    }
    else{
        return 0;
    }
}

int Terminals (struct tile hand[14], int arr[4][4]){ //slight difference
	int TerminalCount = 0, trigger = 0, n = 0;
	struct tile temp[14];
	
	for (int i = 0; i < 14; i++){
		temp[i].suit = 't';
		temp[i].rank = '0';
	}
	
	if (hand[12].rank == 1 || hand[12].rank == 9){
		trigger = 1;
	}
	
	for (int i = 0; i < 4; i++){
		if (arr[i][1] == 1 || arr[i][1] == 9 || arr[i][2] == 1 || arr[i][2] == 9 || arr[i][3] == 1 || arr[i][3] == 9){
			TerminalCount++;
		}
	}
	
	for (int i = 0; i < 4; i++){
		if (arr[i][1] == arr[i][2] && arr[i][1] == arr[i][3]){
			temp[n].suit = arr[i][0];
			temp[n].rank = arr[i][1];
			n++;
		}
	}
	
	int slice = sort(temp, 5);
	
	int Count = 0;
	for (int i = 0; i < 4; i++){
		if (temp[i].rank == 1 || temp[i].rank == 9){
			Count++;
		}
	}
	
	int bool = 0;
	if (n == 3){
		if (temp[0].rank == temp[1].rank-1 && temp[0].rank == temp[2].rank-2){
			bool = 1;
		}
		else{
			bool = 0;
		}
	}
	else if (n == 4){
		if (slice == 1){
			if (temp[1].rank == temp[2].rank-1 && temp[1].rank == temp[3].rank-2) 
				bool = 1;	
			else
				bool = 0;
		}
		if (slice == 3){
			if (temp[0].rank == temp[1].rank-1 && temp[0].rank == temp[2].rank-2)
				bool = 1;
			else
				bool = 0;
		}
		if (slice == 4){
			if (temp[0].rank == temp[1].rank-1 && temp[0].rank == temp[2].rank-2){
				if (temp[0].rank == 1 || temp[2].rank == 9)
					bool = 1;
				else
					bool = 0;
			}
			else if (temp[1].rank == temp[2].rank-1 && temp[1].rank == temp[3].rank-2){
				if (temp[1].rank == 1 || temp[3].rank == 9)
					bool = 1;
				else
					bool = 0;
			}
			else 
				bool = 0;
		}
	}
	
	if (trigger == 0)
		return 0;
	else if (TerminalCount == 4)
		return 1;
	else if (TerminalCount < 2)
		return 0;
	else if (n < 3)
		return 0;
	else if (n == 3){
		if (Count == TerminalCount)
			return 0;
		else if (slice == 3)
			return bool;
		else
			return 0;
	}
	else if (n == 4){
		if (slice == 4) 
			return bool;
		if (slice == 2)
			return 0;
		if (slice == 1){
			if (temp[0].rank == 1 || temp[0].rank == 9)
				return bool;
			else
				return 0;
		}
		if (slice == 3) {
			if (temp[3].rank == 1 || temp[3].rank == 9)
				return bool;
			else
				return 0;
		}
	}
	
	return 0;
}

int _258Triplets(struct tile hand[14]){ 
	int SpecialCount = 0; 
	
	for (int i = 0; i < 14; i++){
		if (hand[i].rank == 2 || hand[i].rank == 5 || hand[i].rank == 8){
			SpecialCount++;
		}
	}
	
	if (SpecialCount == 14){
		return 1;
	}
	else{
		return 0;
	}
}

//A mix between triplets and sequences
int Melds(struct tile hand[14], int arr[4][4]){ 
	int r, c, trigger, bool;
	
	for (r = 0; r < 4; r++){
		for (c = 0; c < 4; c++){
			arr[r][c] = 0;
		}
	}
		
	for (int i = 0; i < 12; i++){
		r = 0;
		trigger = 0;
		
		while (trigger == 0){
			if (r == 4){
				return 0;
			}
			else if (arr[r][0] == 0){
				arr[r][0] = hand[i].suit;
				arr[r][1] = hand[i].rank;
				trigger = 1;
			}
			else if (arr[r][0] != hand[i].suit){
				r++;
			}
			else if (arr[r][2] == 0){
				bool = 0;

				if (arr[r][1] == hand[i].rank && arr[r][1] == hand[i+1].rank){
					bool = 1;
				}
				if (arr[r][1] == hand[i].rank-1){
					bool = 1;
				}
				
				if (bool == 1){
					arr[r][2] = hand[i].rank;
					trigger = 1;
				}
				else{
					r++;
				}
			}
			else if (arr[r][3] != 0){
				r++;
			}
			else{
				bool = 0;

				if (arr[r][1] == arr[r][2] && arr[r][1] == hand[i].rank){
					bool = 1;
				}
				if (arr[r][1] == arr[r][2]-1 && arr[r][1] == hand[i].rank-2){
					bool = 1;
				}
				
				if (bool == 1){
					arr[r][3] = hand[i].rank;
					trigger = 1;
				}
				else{
					r++;
				}
			}
		}
	}
	
	return 1;
}

int FlushBonus(struct tile hand[14]){ 
	int b = 0, c = 0, d = 0, suits;
		
	for (int i = 0; i < 14; i++){
		if (hand[i].suit == 'b'){
			b = 1;
		}
		else if (hand[i].suit == 'c'){
			c = 1;
		}
		else if (hand[i].suit == 'd'){
			d = 1;
		}
	}
		
	suits = b + c + d;
	return suits;
}

int RootBonus(struct tile hand[14], int breakpoint){ 
	int RootCount = 1;
		
	for (int i = 0; i < breakpoint - 3; i++){
		if (hand[i].rank == hand[i+1].rank && hand[i].rank == hand[i+2].rank && hand[i].rank == hand[i+3].rank){
			RootCount = RootCount * 2;
		}
	}
		
	for (int i = breakpoint; i < 11; i++){
		if (hand[i].rank == hand[i+1].rank && hand[i].rank == hand[i+2].rank && hand[i].rank == hand[i+3].rank){
			RootCount = RootCount * 2;
		}
	}
		
	return RootCount;
}

int getScore(const char strHand[]){ 
	struct tile hand[14];
		
	store (strHand, hand);
	int breakpoint = sort(hand, 14);

	//bonus
	int suits = FlushBonus(hand);
	int bonus = RootBonus(hand, breakpoint);
		
	if (suits == 1){
		bonus = bonus * 4;
	}
	else if (suits == 2){
		bonus = bonus * 1;
	}
	else{
		return 0;
	}
		
	int Pairs = AllPairs(hand, breakpoint);
	if (Pairs == 1){
		return 4 * bonus;
	}
		
	int flag = _258Triplets(hand);
		
	int start, stop;
	
	if (breakpoint % 3 == 2){
		start = 0; 
		stop = breakpoint - 1;
	}
	else if (breakpoint % 3 == 0){
		start = breakpoint; 
		stop = 13;
	}
	else{
		return 0;
	}
		
	int flag1 = 0, flag2 = 0;
	struct tile temp;
	int arr[4][4];
		
	for (int i = start; i < stop; i++){
		sort(hand, 14);
		
		if (hand[i].rank == hand[i+1].rank){
		
			temp.rank = hand[13].rank;
			temp.suit = hand[13].suit;
			hand[13].rank = hand[i+1].rank;
			hand[13].suit = hand[i+1].suit;
			hand[i+1].rank = temp.rank;
			hand[i+1].suit = temp.suit;
			
			temp.rank = hand[12].rank;
			temp.suit = hand[12].suit;
			hand[12].rank = hand[i].rank;
			hand[12].suit = hand[i].suit;
			hand[i].rank = temp.rank;
			hand[i].suit = temp.suit;
			
			sort(hand, 12);
			
			int m = Melds(hand, arr);
			if (m == 1){
				flag1 = 1;
				
				int t = Terminals(hand, arr);
				if (t == 1){
					return 4 * bonus;
				}
				
				int tri = Triplets(hand);
				if (tri == 1){
					flag2 = 1;
				}
			}
		}
	}
	
	if (flag1 == 0){
		return 0;
	}
	else if (flag2 == 0){
		return 1 * bonus;
	}
	else if (flag == 1){
		return 8;
	}
	else{
		return 2 * bonus;
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

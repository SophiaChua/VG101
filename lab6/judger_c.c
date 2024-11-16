#include <stdio.h>

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
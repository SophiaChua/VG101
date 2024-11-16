#include "Game.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
void initGame(Game* const game) {
    // It takes about 11 lines of code.
    int j = 0, nums = 123; 

    game -> turnCnt = 0; 
    game -> possibleCnt = MAX_POSSIBLE; 
    while (j < MAX_POSSIBLE)
    {
        if (isValidNum(nums))
        {
            game -> num[j] = nums;
            j++;  
        }
        nums++; 
    }
    for (int i = 0; i < MAX_POSSIBLE; i++)
        game -> isPossible[i] = true; 
    game -> guesses[1] = 0; 
    game -> results[0].A = 0;
    game -> results[0].B = 0; 
}
Result judgeGuess(const int correctNum, const int guessNum) {
    // It takes about 10 lines of code.
    int A = 0, B = 0;

    for (int n = 1; n <= 4; n++)
    {
        for (int m = 1; m <= 4; m++)
        {
            if (getDigit(correctNum, n) == getDigit(guessNum, m) && n == m)
                A++; 
            else if (getDigit(correctNum, n) == getDigit(guessNum, m) && n != m)
                B++; 
        }
    }

    return (Result){A, B}; 
}
void updateGameWithTurn(Game* const game, const int turn) {
    // It takes about 10 lines of code.
    int A = game -> results[turn].A;
    int B = game -> results[turn].B; 
    int count = 0; 
    
    for (int j = 0; j < MAX_POSSIBLE; j++)
    {
        int x = judgeGuess(game -> guesses[turn], game -> num[j]).A;
        int y = judgeGuess(game -> guesses[turn], game -> num[j]).B;
        if (x!= A || y != B)
        {
            game -> isPossible[j] = false; 
        }
        else if (game -> isPossible[j] == true)
        {
            count++; 
        }
    }
    game -> possibleCnt = count; 
}
GameResult takeGuessResult(Game* const game, const int guess, const Result result) {
    // It takes about 11 lines of code.
    game -> turnCnt++; 
    game -> guesses[game -> turnCnt] = guess; 
    game -> results[game -> turnCnt].A = result.A;
    game -> results[game -> turnCnt].B = result.B; 
    updateGameWithTurn(game, game -> turnCnt); 

    int status = game -> possibleCnt; 
    if (result.A == 4)
        return Correct; 
    else if (status == 0)
        return Impossible; 
    else 
        return Ongoing; 
}
void revert1Turn(Game* const game) {
    // It takes about 12 lines of code.
    if (game -> turnCnt == 0)
        printf("This is turn #1. Cannot revert."); 
    else 
    {
        int p[MAX_POSSIBLE]; 
        Result q[20]; 
        int x = game -> turnCnt; 
        
        for (int i = 1; i < MAX_POSSIBLE; i++)
        {
            p[i] = game -> guesses[i]; 
        }
        for (int j = 1; j < 20; j++)
        {
            q[j].A = game -> results[j].A;
            q[j].B = game -> results[j].B;
        }

        initGame(game); 

        for(int n = 1; n < x-1; n++)
        {
            game -> results[n].A = q[n].A;
            game -> results[n].B = q[n].B;
            game -> guesses[n] = p[n]; 
            updateGameWithTurn(game, n);
        }
    }
}
int makeGuess(const Game* const game) {
    // It takes about 5 lines of code.
    int trigger = 1; 

    while (trigger = 1)
    {
        int random = rand() % MAX_POSSIBLE; 
        if(game -> isPossible[random])
        {
            return game -> num[random]; 
            trigger = 0; 
        }
    }
}

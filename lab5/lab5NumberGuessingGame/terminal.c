#include "terminal.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"
#define WIDTH (85)
int beforeTurn(const Game* const game) {
    // This function has been implemented, you can read the code to get a sense of how this function works.
    printf("------------------------------\n");
    printf("Turn #%d. The number of possible answer is %d. AI's choice is to guess ", game->turnCnt + 1, game->possibleCnt);
    int aiGuess = makeGuess(game);
    printNum(aiGuess);
    puts("");
    return aiGuess;
}
int requestNewGuess(const int aiGuess) {
    // It takes about 17 lines of code.
    char s[] = "Input a guess, press enter to take AI's choice, or input '-' to revert 1 turn:";
    printWithWidth(s,85);
    char input[10] = ""; 

    while(1)
    {
        fgets(input, sizeof(input), stdin); 
        if (input[0] == '\n') 
        { 
            return aiGuess;
        }
        else if (isdigit(input[1]))
        {
            int num = atoi(input);
            if (isValidNum(num))
            {
                return num; 
            }
            else
            {
                char error[] = "Your guess is invalid. Input again:";
                printWithWidth(error,85);
                continue; 
            }
        }
        else if (input[0] == '-')
        {
            printf("Revert to last turn.\n"); 
            return -1;
        }
    }
}
Result requestNewGuessResult(const int guess) {
    // It takes about 12 lines of code.
    char buffer[100] = ":"; 
    char invalid[100] = "Your result is invalid. Input again:"; 
    Result res; 

    printf("Input the result of the new guess ");
    printNum(guess); 
    printWithWidth(buffer, 46); 
    
    while (1)
    {
        scanf("%d%d", &(res.A), &(res.B)); 
        if (isValidResult(res))
            return res;
        else 
        {
            printWithWidth(invalid, 85); 
        }
    }
}
void endGame(const Game* const game, const GameResult gameResult) {
    // It takes about 6 lines of code.
    if (gameResult == 1)
    {
        printf("------------------------------\n"); 
        printf("Congratulations! You've guessed the correct number in %d steps!\n", game -> turnCnt);
    }
    else if (gameResult == 2)
    {
        printf("------------------------------\n"); 
        printf("Oops! It seems that there's something wrong with the input, since a number satisfying such input does not exist.\n"); 
    }
}

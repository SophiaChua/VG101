#include "utils.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Game.h"

bool isValidNum(int num) {
    // It takes about 13 lines of code.
    if (num < 100)
        num = num * 100; 
    else if (num >= 100 && num < 1000)
        num = num * 10; 

    int r, temp = num; 
    int check[10] = {0}; 

    while (temp != 0)
    {
        r = temp % 10; 

        if(check[r] == 1)
            break; 
        else 
            check[r] = 1; 

        temp = temp / 10; 
    }

    if (temp != 0 || num > 9999 || num <= 0)
        return false; 
    else
        return true; 
}

void printWithWidth(const char s[], const int width) {
    // It takes about 4 lines of code.
    int length = strlen(s); 
    char buffer[255] = ""; 
    
    if (length < width)
    {
        strcpy(buffer, s); 
        memset(buffer+length, ' ', width - length);
        buffer[length + width] = '\0'; 
        printf("%s", buffer); 
    }
}

int test(int aiGuess)
{
    // It takes about 17 lines of code.
    char s[] = "Input a guess, press enter to take AI's choice, or input '-' to revert 1 turn:";
    printWithWidth(s,85);
    char input[10] = ""; 

    while(1)
    {
        fgets(input, sizeof(input), stdin); 
        if (input[0] == '\n') 
        { 
            printf("yes"); 
            return aiGuess;
        }
        else if (isdigit(input[0]))
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

int main()
{

    int aiGuess = 1234; 
    test(aiGuess); 
}
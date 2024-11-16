#include "utils.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "Game.h"
int getDigit(const int num, const int digitPos) {
    // It takes about 1 line of code.
    return num / (int)pow(10, 4 - digitPos) % 10;  
}
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
bool isValidResult(const Result res) {
    // It takes about 8 lines of code.
    int sum = res.A + res.B; 

    if (res.A < 0 || res.A > 4 || res.B < 0 || res.B > 4)
        return false; 
    else if (res.A == 3 && res.B == 1)
        return false; 
    else if (sum > 4 || sum < 0)
        return false; 
    else if (sum >= 0 && sum <= 4)
        return true; 
}
void printNum(const int num) {
    // It takes about 3 lines of code.
    for (int i = 1; i <= 4; i++)
        printf("%d", getDigit(num, i)); 
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
    else 
    {
        printf("%s",s); 
    }
}

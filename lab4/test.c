#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_LENGTH 255

int isOperator(char c) 
{
    switch (c) {
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '^': 
        return 2;
        break; 
        default: 
        return 1;
    }
}

int main ()
{
    FILE *fp; 
    char input[MAX_LENGTH] = "";
    char temp[MAX_LENGTH] = ""; 
    
    fp = fopen("commands.txt", "r");
    
    while(fgets(input, MAX_LENGTH, fp) != NULL)
    {
        if (input[0] != '\n')
        {
            temp[strcspn(temp, "\n")] = "";
            strcat(temp, input); 
            printf("%s", temp); 
        }
        else 
        {
            strcpy(temp, input); 
        }
    }
    
    fclose(fp);

    return 0; 
}
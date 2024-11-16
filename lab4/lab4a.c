#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_ROWS 300
#define MAX_LENGTH 225

char stack1[MAX_LENGTH];
int top = 0; 

void push(char x)
{
    stack1[top++] = x;   
}

char pop()
{
    if (top != 0)
    {
        return stack1[--top]; 
    }
}

int priority(char x)
{
    if (x == '(')
        return 0; 
    else if (x == '+' || x == '-')
        return 1; 
    else if (x == '*' || x == '/')
        return 2; 
    else if (x == '^')
        return 3;  
}

char infix_to_postfix(char input)
{
    char x;
    char print[MAX_LENGTH]; 
    int n = 0; 

    for (int i = 0; i < strlen(input); i++)
    {
        //printf("%3c", input[i]); 
        if (isdigit(input[i]))
        {
            print[n++] = input[i]; 
            //printf("Operand: %c\n", input[i]); 
        }
        else if (input[i] == '.')
        {
            print[n++] = input[i];
            //printf("Decimal: %c\n", input[i]);
        }
        else if (input[i] == '(')
        {
            push(input[i]); 
        }
        else if (input[i] == ')')
        {
            while ((x = pop()) != '(')
            {
                print[n++] = pop(); 
                printf("Pop(')'): %c\n", input[i]);
            }
        }
        else if (input[i] = ' ')
        {
            continue; 
        }
        else 
        {
            while (stack1[top] != 0 && priority(stack1[top]) >= priority(input[i]))
            {
                print[n++] = pop();
                printf("Pop(operators): %c\n", pop());
            }
            push(input[i]); 
        }
    }

    while (top != 0)
    {
        print[n++] = pop(); 
    }

    //printf("%s\n", print); 
}


int main ()
{
    FILE *fp; 
    char input[MAX_ROWS][MAX_LENGTH];
    int row = 0;  

    fp = fopen("commands.txt", "r");
    
    while(fgets(input[row], 255, fp) != NULL)
    {
        row++;
    }

    for (int j = 0; j < row; j++)
    {
        //printf("%s\n", input[j]);
    } 

    infix_to_postfix(input);

    fclose(fp);
}
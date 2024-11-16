#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_LENGTH 255

double stack[MAX_LENGTH] = {0.0};
int top = -1; 

int isEmpty() {
    if (top == -1) 
        return 1;
    return 0;
}

int isFull() {
    if (top == MAX_LENGTH)
        return 1;
    return 0;
}

double peek() {
    return stack[top];
}

void push(double x)
{
    if (!isFull()) {
        top++;
        stack[top] = x;
    } 
    else {
        printf( "Stack is full.\n" );
    }
}

double pop()
{
    double x;

    if (!isEmpty) {
        x = peek();
        --top;
        return x;
    } else {
        printf( "Stack is empty.\n" );
    }
}

int priority(char x)
{
    switch (x)
    {
        case '(':
            return 0; 
            break;
        case '+':
        case '-':
            return 1; 
            break; 
        case '*':
        case '/':
            return 2; 
            break; 
        case '^':
            return 3; 
            break; 
    }
}

int isOperator(char c) {
    switch (c) {
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '^': return 2;
        default: return 1;
    }
}

double RVP_decimals(int i, char* string) {

    double RVP = 0.0;
    int decimalPlace = 0;
    int j = i;  

    while (*(string + j) != ' '|| isOperator(*(string + j)) != 2) {
        if (isdigit(*(string + j))) {
            int cInt = *(string + j) - '0';  
            if (decimalPlace == 0)
                RVP = RVP * 10 + cInt;
            else {
                RVP = RVP + cInt / pow(10, decimalPlace);
                decimalPlace++;
            }
        }

        if (*(string+j) == '.') {
            decimalPlace = 1;
        }

        j++;
    }
}

int RVPcount(int i, char* string) {
    int j = i, k = 0;
    while (*(string+j+1) != ' '|| isOperator(*(string+j+1)) != 2) {
        k++;
    }
    return k;
}

void infix_to_postfix(char* input)
{
    char x; 
    int n = 0, m = 0; 
    double RVP[120] = {0.0}; 
    int helper[120] = {0};

    printf("%s", input);

    while (*(input+n) != '\0') {
        char c = *(input+n);
        
        if (c == ' ') continue;

        if (isdigit(c))
        {
            RVP[m] = RVP_decimals(n, input);
            n += RVPcount(n, input);
            helper[m] = 1; 
            m++;
        }
        else if (c == '(')
        {
            push(c); 
        }
        else if (isEmpty() || peek() == '(')
        {
            push(c);
        }
        else if (c == ')')
        {
            while (peek() != '(') {
                RVP[m] = pop();
                helper[m] = 2;
                m++;
            }
            pop();
        }
        else { 
            while (priority(c) <= priority(peek())) {
                RVP[m] = pop();
                helper[m] = 2;
                m++;
            }
            push(c);
        }

        while (!isEmpty) {
            if (peek() != '(') 
            {
                RVP[m] = pop();
                helper[m] = 2;
                m++;
            }
            else
                pop();
        }
        printf("%f", RVP[m]); 
    }
}

int main ()
{
    FILE *fp; 
    char *input;
    
    fp = fopen("commands.txt", "r");
    
    while(fgets(input, MAX_LENGTH, fp) != NULL)
    {
        //printf("%s", input); 
        infix_to_postfix(input); 
    }
    
    fclose(fp);

    return 0; 
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_LENGTH 120

double stack[MAX_LENGTH] = {0.0};
int top = -1; 

char vars[20][15] = {{'0'}}; 
int varNums = 0;
double varValue[20] = {0.0};

void makeEmpty()
{
    top = -1; 
}

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

void push(int x)
{
    if (!isFull()) {
        top++;
        stack[top] = x;
    } 
}

void push2(double x)
{
    top++;
    stack[top] = x; 
}

double pop()
{
    double x;

    x = peek();
    //printf("pop: %lf\n", x); 
    --top;
    return x;
}

int priority(char x)
{
    int precedence = 0; 

    switch (x)
    {
        case '(':
            precedence = 0; 
            break;
        case '+':
        case '-':
            precedence = 1; 
            break; 
        case '*':
        case '/':
            precedence = 2; 
            break; 
        case '^':
            precedence = 3; 
            break; 
    }

    return precedence; 
}

int isOperator(char c) {
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

double RVP_decimals(int i, char* string) {

    double RVP = 0.0; 
    int decimalPlace = 0; 
    int j = i;

    //printf("i = %d\n", j);
    //printf("c: %c\n", string[i]); 

    while (isdigit(*(string + j)) || *(string + j) == '.') {
        if (isdigit(*(string + j))) {
            int cInt = *(string + j) - '0';  
            //printf("cInt: %lf\n", cInt); 
            if (decimalPlace == 0)
                RVP = RVP * 10 + cInt;
            else {
                RVP = RVP + cInt / pow(10, decimalPlace);
                decimalPlace++;
            }
           // printf("RVP: %lf\n", RVP); 
        }

        if (*(string + j) == '.') {
            decimalPlace = 1;
        }
        j++; 
    }

    return RVP; 
}

int RVPcount(int i, char* string) {
    int k = 0;

    //printf("i: %d\n", i);
    //printf("c: %c\n", *(string+i));

    while (isdigit(*(string + i)) || *(string + i) == '.') {
        k++;
        i++; 
    }

    //printf("k: %d\n", k); 
    return k - 1;
}

int RVPcountVar(int i, char* string)
{

    while (!isOperator(*(string + i)) || *(string + i) != '\0')
    {
        i++; 
    }
    //printf("i: %d\n", i); 
    return i; 
}

double infix_to_postfix(char* input)
{
    char c; 
    int n = 0, m = 0, l = 0; 
    double RVP[120] = {0.0}; 
    int helper[120]; 

    //printf("%s\n", input);

    makeEmpty(); 
    
    //while(*(input+n) != '\0')
    //{
    //    printf("c = %c\n", *(input+n)); 
    //    n++;
    //}
    

    while (*(input + n) != '\0') {

        c = *(input + n);
        
        //printf("c: %c\n", c); 

        if (c == ' ') 
        {
            n++; 
            continue; 
        }

        if (isdigit(c))
        {   
            RVP[m] = RVP_decimals(n, input);
            //printf("RVP[m]: %lf\n", RVP[m]);
            n += RVPcount(n, input);
            helper[l] = 1; 
            //printf("helper: %d\n", helper[l]);
            //printf("n = %d\n", n);
            m++;
            l++;   
        } 
        else if (c >= 'a' && c <= 'z')
        {
            int count = 0;

            for (int i = 0; i < varNums; i++)
            {
                if (c == vars[i][0]) 
                {
                    //printf("n: %d\n", n); 
                    //printf("c: %c\n", c); 
                    //printf("var: %c\n", vars[i][0]); 
                    //printf("varVal: %lf\n", varValue[i]); 
                    //printf("i: %d\n", i); 
                    RVP[m] = varValue[i]; 
                    helper[l] = 1; 
                    //printf("m: %d\n", m); 
                    //printf("helper: %d\n", helper[l]); 
                    //printf("l: %d\n", l); 
                    //printf("RVP: %lf\n", RVP[m]);
                    count = RVPcountVar(n, input);
                    //printf("counter: %d\n", count); 
                }
            }
            n = count; 
            //printf("n: %d\n", n); 
        }
        else if (c == '(')
        {
            push(c); 
        }
        else if (c == ')')
        {
            while (peek() != 40.0) 
            {
                //printf("stack: %lf\n", stack[top]);
                RVP[m] = pop();
                //printf("RVP: %lf\n", RVP[m]);
                helper[l] = 2;
                //printf("helper: %d\n", helper[l]);
                //printf("stack: %lf\n", stack[top]);
                m++;
                l++; 
            }
            pop();
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            while (priority(c) <= priority(peek())) {
                RVP[m] = pop();
                //printf("RVP: %lf\n", RVP[m]);
                helper[l] = 2; 
                //printf("helper: %d\n", helper[l]);
                m++;
                l++; 
            }
            push(c);
        }
        n++;
        //printf("n = %d\n", n);   
        //printf("top: %d\n", top);
        //printf("stack: %lf\n", stack[top]);
        //for (int q = 0; q < m; q++)
        //    printf("RVP: %8lf\n", RVP[q]);
        //printf("helper: "); 
        //for (int w = 0; w < l; w++)
        //    printf("%2d", helper[w]);
    }
        

    while (top >= 0) {
        //printf("top: %d\n", top);
        //printf("stack: %lf\n", stack[top]); 
        if (peek() != '(')
        {
        RVP[m] = pop();
        //printf("RVP: %lf\n", RVP[m]);
        helper[l] = 2;
        //printf("helper: %d\n", helper[l]);
        m++;
        l++; 
        }
        //else if (peek() == '(')
        //    pop(); 
    }

    //printf("top: %d\n", top);
    //printf("stack: %lf\n", stack[top]); 
    
    int w = 0; 
    
    for (int q = 0; q < m; q++)
    {
        double val1, val2; 

        //printf("RVP: %12lf\n", RVP[q]); 
        //printf("w = %d\n", w); 
        //printf("helper: %3d\n", helper[w]);
        
        if (RVP[q] == 43.0 && helper[w] == 2) //addition (+)
        {
            val1 = pop();
            val2 = pop();
            //printf("val1: %lf\n", val1);
            //printf("val2: %lf\n", val2);
            push2(val2 + val1); 
            //printf("add: %lf\n", stack[top]); 
        }
        else if (RVP[q] == 45.0 && helper[w] == 2) //subtraction (-)
        {
            val1 = pop();
            val2 = pop(); 
            push2(val2 - val1);
            //printf("sub: %lf\n", stack[top]); 
        }
        else if (RVP[q] == 42.0 && helper[w] == 2) //multiplication (+)
        {
            val1 = pop();
            val2 = pop();
            push2(val2 * val1); 
            //printf("multiply: %lf\n", stack[top]); 
        }
        else if (RVP[q] == 47.0 && helper[w] == 2) //division (/)
        {
            val1 = pop();
            val2 = pop(); 
            push2(val2 / val1);
            //printf("divide: %lf\n", stack[top]); 
        }
        else if (RVP[q] == 94.0 && helper[w] == 2) // power(^)
        {
            val1 = pop();
            val2 = pop();
            push2(pow(val2, val1)); 
            //printf("power: %lf\n", stack[top]); 
        }
        else if (helper[w] == 1)
        {
            push2(RVP[q]); 
        }

        w++; 
        //printf("w = %d\n", w); 
    }

    //printf("top: %d\n", top); 

    //printf("%lf\n", stack[top]); 
    return 0;  
}

double variables(char *input)
{ 
    char s[MAX_LENGTH] = ""; 
    int i = varNums, j = 0, n = 0, m = 0; 

    printf("input: %s\n", input); 
    //printf("input: %c\n", *(input + n));

    while (*(input + n) != '=')
    {
        *(*(vars + i) + j) = *(input + n); 
        j++; 
        n++; 
    }

    while(*(input + n) != '\0')
    {
        if (*(input + n) == '=')
        {
            n++; 
            continue; 
        }
        else 
        {
            s[m++] = *(input + n);  
        }
        n++; 
    }

    int s_length = strlen(s); 

    if (s_length - 1 == ';')
    {
        s[s_length - 1] = '\0'; 
        infix_to_postfix(s);
    }
    else 
    {
        infix_to_postfix(s);
        printf("%lf\n", stack[top]); 
    }
    
    varValue[varNums] = stack[top]; 
    //printf("n: %d\n", n); 
    //printf("new input: %c\n", *(input + n));
    //printf("variables: %s\n", vars[varNums]); 
    //printf("varVal: %lf\n", varValue[varNums]); 
    varNums++;
    //printf("values: %s\n", s); 

    return 0;
}

void fixString(char in[], char input[])
{
    int length = strlen(in);
    int j = 0;
    char temp[MAX_LENGTH] = "\0";

    if (in[length - 1] == '\n')
    {
        in[length - 1] = '\0'; 
    }

    for (int i = 0; i < length; i++)
    {
        if (in[i] != ' ')
        {
            temp[j++] = in[i]; 
        }
        temp[j] = '\0'; 
    }

    int m = 0;
    for (int n = 0; n < length; n++)
    {
        if (temp[n] == '-')
        {
            if (n == 0 || temp[n - 1] == '(')
            {
                input[m++] = '0';
                input[m++] = '-'; 
            }
            else 
            {
                input[m++] = '-';
            }
        }
        else 
        {
            input[m++] = temp[n]; 
        }
    }
}

int main ()
{
    FILE *fp; 
    char in[MAX_LENGTH] = "\0";
    
    fp = fopen("commands.txt", "r");
    
    while(fgets(in, MAX_LENGTH, fp))
    {
        char input[MAX_LENGTH];
        fixString(in, input);  
        variables(input); 
    }
    
    fclose(fp);

    return 0; 
}
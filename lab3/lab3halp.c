#include <stdio.h>
#include <string.h>

int max(char* input, int inputCount)
{ 
    int currentTerm; 
    int max = input[0]; 

    for (int i = 0; i < inputCount; i++)
    {
        if (input[i] > max)
        {
            if (input[i] >= '0' && input[i] <= '9' || input[i] >= 'a' && input[i] <= 'z')
                {
                    max = input[i];
                }
        }
    }
    return max; 
}

int min(char* input, int inputCount)
{ 
    int currentTerm; 
    int min = input[0]; 

    for (int i = 0; i < inputCount; i++)
    {
        if (input[i] < min)
        {
            if (input[i] >= '0' && input[i] <= '9' || input[i] >= 'a' && input[i] <= 'z')
                {
                    min = input[i];
                }
        }
    }
    return min; 
}

int main()
{
    while(1)
    {
        char input[1000]; 
        int currentTerm; 
        int i = 0; 
        int count = 0; 
        int odd = 0;
        int max = input[0]; 
        int min = input[0];
        int maximum;
        int minimum;
        int sum = 0;
        double average;
        double product = 1;

        scanf("%s", &input); 
        int inputCount = strlen(input); 

        for (i = 0; i < inputCount; i++)
            {
                if (input[i] >= '0' && input[i] <= '9')
                {
                    currentTerm = input[i] - 48; 
                    count++; 
                    sum += currentTerm; 
                    product = product*currentTerm;
                    if (currentTerm % 2 == 1)
                    {
                        odd++; 
                    }
                }
                else if (input[i] >= 'a' && input[i] <= 'z')
                {
                    currentTerm = input[i] - 87;
                    count++; 
                    sum += currentTerm; 
                    product = product*currentTerm;
                    if (currentTerm % 2 == 1)
                    {
                        odd++; 
                    }
                } 
            }

        average = (double)sum / (double)count; 
        maximum = max(input, inputCount); 
        minimum = min(input, inputCount); 
        if (maximum >= '0' && maximum <= '9')
        {
            maximum = maximum - 48; 
        }
        if (maximum >= 'a' && maximum <= 'z')
        {
            maximum = maximum - 87; 
        }
        if (minimum >= '0' && minimum <= '9')
        {
            minimum = minimum - 48; 
        }
        if (minimum >= 'a' && minimum <= 'z')
        {
            minimum = minimum - 87; 
        }
        if (count == 0)
        {
            break; 
        }
        
        printf("Count: %d\n", count);
        printf("Odd: %d\n", odd); 
        printf("Maximum: %d\n", maximum); 
        printf("Minimum: %d", minimum); 
        printf("Average: %f\n", average); 
        printf("Sum: %d\n", sum);
        printf("Product: %g\n", product); 
    }
}
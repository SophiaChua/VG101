#include <stdio.h>
#include <string.h>

int main()
{
    while(1)
    {
        char input[1000]; 
        int currentTerm; 
        int i = 0; 
        int count = 0; 
        int odd = 0;
        int maximum;
        int minimum; 
        int sum = 0;
        double average;
        double product = 1;

        fgets(input, 1000, stdin); 
        int inputCount = strlen(input); 
        
        for (i = 0; i < inputCount; i++)
        {
            if (input[i] >= '0' && input[i] <= '9' || input[i] >= 'a' && input[i] <= 'z')
            {
                minimum = input[i];
                maximum = input[i];
                break; 
            }
            else 
            {
                continue; 
            }
        }

        for (i = 0; i < inputCount; i++)
        {
            if (input[i] >= '0' && input[i] <= '9')
            {
                currentTerm = input[i] - '0'; //can use '0' instead of - 48 
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

        for (i = 0; i < inputCount; i++)
        {
            if (input[i] > maximum)
            {
                if (input[i] >= '0' && input[i] <= '9' || input[i] >= 'a' && input[i] <= 'z')
                {
                    maximum = input[i];
                }
            }
            if (input[i] < minimum)
            {
                if (input[i] >= '0' && input[i] <= '9' || input[i] >= 'a' && input[i] <= 'z')
                {
                    minimum = input[i]; 
                }
            }
        }

        average = (double)sum / (double)count; 
        
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

        printf("count:%d\n", count);
        printf("odd:%d\n", odd); 
        printf("maximum:%d\n", maximum); 
        printf("minimum:%d\n", minimum); 
        printf("average:%f\n", average); 
        printf("sum:%d\n", sum);
        printf("product:%g\n", product);  
    }
}
// You can include libraries you need
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// hw6 - finish this function
void sortstr(char str[]) {
    // TODO: write your code here 
    unsigned int n = 0; 
    int numStr[10], temp, num[30] = {0}, v = 0, m = 0; 
    char buffer[50] = "";  

    //printf("input: %s\n", str); 

    //Step 1: Change the numbers into the int datatype
    while (n <= strlen(str))
    {
        if (isdigit(str[n]))
        {
            num[m] = num[m] * 10 + (str[n] - '0'); 
        }
        else if (str[n] == ' ' || str[n] == '\0')
        {
            numStr[v++] = num[m]; 
            m++; 
        }
        n++; 
    }

    //Step 2: Sort the numbers 
    for (int i = 0; i < v - 1; i++)
    {
        for (int j = 0; j < v - 1 - i; j++)
        {
            if (numStr[j] > numStr[j+1])
            {
                temp = numStr[j];
                numStr[j] = numStr[j+1];
                numStr[j+1] = temp; 
            }
        }
    }

    strcpy(str, ""); 

    for (int k = 0; k < v; k++)
    {
        //printf("numStr: %d\n", numStr[k]); 
        sprintf(buffer, "%d ", numStr[k]);
        strcat(str, buffer); 
    }
}

// Do NOT change the following lines.
int main() {
    char str[256];
    scanf("%[^\n]%*c", str);  // ask for the user input
    sortstr(str);
    printf("%s\n", str);  // output
    return 0;
}

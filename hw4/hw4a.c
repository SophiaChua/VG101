#include <stdio.h>
#include <math.h>
#include <string.h>

int dec_to_hex(unsigned long long decNum)
{
    int i = 1, j, r; 
    char hexNum[500]; 

    if (decNum != 0)
    {
        while (decNum != 0)
        {
            r = decNum % 16; 
            if (r < 10)
            {
                r += '0'; 
            }
            else 
            {
                r += 55; 
            }
            hexNum[i++] = r; 
            decNum = decNum/16; 
        }
        for (j = i - 1; j > 0; j--)
        {
            printf("%c", hexNum[j]); 
        }
    }
    else if (decNum == 0)
    {
        strcpy(hexNum, "0"); 
        printf("%s", hexNum); 
    }
    return 0; 
}

int main()
{
    char hex1[255], hex2[255]; 
    char hexDigits[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; 
    unsigned long long dec1 = 0, dec2 = 0, decSum, decDiff; 
    int power1 = 0, power2 = 0, val1, val2; 

    printf("hexadecimal number 1: "); 
    scanf("%s", hex1); 
    printf("hexadecimal number 2: "); 
    scanf("%s", hex2); 

    
    /*convert hexadecimal inputs to decimal numbers*/
    for (int i = strlen(hex1)-1; i >= 0; i--)  
    {
        for (int j = 0; j < 16; j++)
        {
            if (hex1[i] == hexDigits[j]) 
            {
                dec1 += j*pow(16, power1); 
            }
        }
        power1++; 
    }

    for (int n = strlen(hex2)-1; n >= 0; n--)  
    {
        for (int m = 0; m < 16; m++)
        {
            if (hex2[n] == hexDigits[m]) 
            {
                dec2 += m*pow(16, power2); 
            }
        }
        power2++; 
    }
    

    //printf("dec1: %d\n", dec1);
    //printf("dec2: %d\n", dec2); 

    decSum = dec1 + dec2; 
    decDiff = dec1 - dec2; 

    //printf("sum: %d\n", decSum);
    //printf("difference: %d\n", decDiff);

    printf("Their sum is "); // hexSum = hex1 + hex2 
    dec_to_hex(decSum); 
    printf("\n"); 
    printf("Their difference is "); // hexDiff = hex1 – hex2
    dec_to_hex(decDiff); 

    return 0; 
} 

/*
References: 
    https://btechgeeks.com/c-program-to-convert-hexadecimal-number-to-decimal-number-system/ 
    https://www.geeksforgeeks.org/c-program-for-hexadecimal-to-decimal-conversion/ 
    https://www.geeksforgeeks.org/c-program-for-decimal-to-hexadecimal-conversion/?ref=rp 
    https://btechgeeks.com/c-program-to-convert-decimal-number-to-hexadecimal-number/ 
    https://www.programmingsimplified.com/c-program-reverse-string#:~:text=C%20program%20to%20reverse%20a%20string%201%20Reverse,program%20to%20reverse%20a%20string%20using%20pointers%20
    https://www.includehelp.com/c/c-program-to-read-string-with-spaces-using-scanf-function.aspx 

Functions Used: 
    https://www.geeksforgeeks.org/strrev-function-in-c/
    https://www.includehelp.com/c/modulus-of-two-float-or-double-numbers-in-c-language.aspx 
*/
#include <stdio.h>
#include <string.h>

int hex_to_dec(char hex)
{
    int val = 0; 

    if (hex >= '0' && hex <= '9')
    {
        val = hex - '0';
    }
    else if (hex >= 'A' && hex <= 'F')
    {
        val = hex - 'A' + 10; 
    }

    return val; 
}

int dec_to_hex(int dec)
{
    int r;
    char hex; 
    
    r = dec % 16; 
    if (r < 10)
    {
        r += '0'; 
    }
    else 
    {
        r += 55; 
    }
    hex = r;

    return hex; 
}

int main()
{
    char hex1[255], hex2[255], hexSum[255], hexDiff[255];
    int sum[255], diff[255];
    int carry1 = 0, carry2 = 0, k = 0, o = 0, index1 = 0, index2 = 0, trigger1 = 0, trigger2 = 0; 
    
    printf("hexadecimal number 1: "); 
    scanf("%s", hex1); 
    printf("hexadecimal number 2: "); 
    scanf("%s", hex2); 

    int i = strlen(hex1) - 1;
    int n = strlen(hex2) - 1; 

    /*adding hexadecimal numbers*/
    for (; i >= 0 && n >= 0; i--, n--, index1++, k++)
    {   
        sum[k] = (hex_to_dec(hex1[i]) + hex_to_dec(hex2[n]) + carry1) % 16; 
        carry1 = (hex_to_dec(hex1[i]) + hex_to_dec(hex2[n]) + carry1) / 16; 
        hexSum[index1] = dec_to_hex(sum[k]); 
        //printf("sum: %d\n", sum[k]); 
        //printf("carry1: %d\n", carry1); 
        //printf("hexSum: %c\n", hexSum[index1]); 
    }
    
    for (; i >= 0; i--)
        {
            sum[k] = (hex_to_dec(hex1[i]) + carry1) % 16;
            carry1 = (hex_to_dec(hex1[i]) + carry1) / 16; 
            hexSum[index1++] = dec_to_hex(sum[k]);
            //printf("sum: %d\n", sum); 
            //printf("carry1: %d\n", carry1); 
            //printf("hexSum: %c\n", hexSum[index1]); 
        }
    
    int j = strlen(hex1) - 1; 
    int m = strlen(hex2) - 1;

    /*subtracting hexadecimal numbers*/
    for (; j >= 0 && m >= 0; j--, m--, index2++, o++)
    {
        diff[o] = ((hex_to_dec(hex1[j]) - hex_to_dec(hex2[m]) - carry2));
        if (diff[o] < 0)
        {
            diff[o] += 16; 
            carry2 = 1; 
        }
        else
        {
            carry2 = 0; 
        }
        hexDiff[index2] = dec_to_hex(diff[o]); 
        //printf("difference: %d\n", diff[o]);
        //printf("hexDiff: %c\n", hexDiff[index2]);
    }

    for (; j >= 0; j--)
    {
        diff[o] = (hex_to_dec(hex1[j]) - carry2);
        hexDiff[index2++] = dec_to_hex(diff[o]);
        if (diff[o] < 0)
        {
            diff[o] += 16; 
            carry2 = 1; 
        }
        else 
        {
            carry2 = 0; 
        }
    }

    int sumCounter = strlen(hexSum);
    int diffCounter = strlen(hexDiff);
    int sumCondition = 0, diffCondition = 0;

    for (; sumCounter > 0; sumCounter--)
    {
        if (hexSum[sumCounter-1] != '0')
        {
            sumCondition++;
        }
    }
    for (; diffCounter > 0; diffCounter--)
    {
        if (hexDiff[diffCounter-1] != '0')
        {
            diffCondition++;
        }
    }
    
    printf("Their sum is "); 
    for (; index1 >= 0; index1--)
    {
        if (sumCondition == 0)
        {
            printf("0");
            break;
        }
        if (hexSum[index1] == '0' && trigger1 == 0)
        {
            continue; 
        }
        else
        {
            trigger1 = 1; 
        }
        printf("%c", hexSum[index1]); 
    }
    printf("\n"); 

    printf("Their difference is ");
    for (; index2 >= 0; index2--)
    {
        if (diffCondition == 0)
        {
            printf("0");
            break;
        }
        if ((hexDiff[index2] == '0') && (trigger2 == 0))
        {
            continue; 
        }
        else 
        {
            trigger2 = 1; 
        }
        printf("%c", hexDiff[index2]);    
    }
    printf("\n");

    /*int u = 0; 
    while (hexDiff[u] == '0' && strlen(hexDiff) - u != 1)
    {
        u++;
    }  
    strcpy(hexDiff, hexDiff+u); 
    */
}

/*References
    https://ccssmathanswers.com/hexadecimal-addition-and-subtraction/ 
    https://www.geeksforgeeks.org/sum-two-large-numbers/ 
    https://www.geeksforgeeks.org/difference-of-two-large-numbers/ 
*/
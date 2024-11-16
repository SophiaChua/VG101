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
    int diffCondition = 0; 
    
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
    }
    
    for (; i >= 0; i--, index1++)
        {
            sum[k] = (hex_to_dec(hex1[i]) + carry1) % 16;
            carry1 = (hex_to_dec(hex1[i]) + carry1) / 16; 
            hexSum[index1] = dec_to_hex(sum[k]);
        }

    if (carry1 != 0)
    { 
        hexSum[index1++] = carry1 + '0'; 
    }
    
    int j = strlen(hex1) - 1; 
    int m = strlen(hex2) - 1;

    if (strcmp(hex1, hex2) == 0)
    {
        diffCondition = 1; 
    }

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

    index1 = index1 - 1; 
    index2 = index2 - 1; 

    printf("Their sum is "); 
    for (; index1 >= 0; index1--)
    {
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
    if (diffCondition == 1)
    {
        printf("0"); 
    }
    for (; index2 >= 0; index2--)
    {
        if (hexDiff[index2] == '0' && trigger2 == 0)
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
}

/*References
    https://ccssmathanswers.com/hexadecimal-addition-and-subtraction/ 
    https://www.geeksforgeeks.org/sum-two-large-numbers/ 
    https://www.geeksforgeeks.org/difference-of-two-large-numbers/ 
*/
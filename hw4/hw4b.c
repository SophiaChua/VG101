#include <stdio.h>

int main()
{
    unsigned long long hex1, hex2, hexSum, hexDiff;  
    
    printf("hexadecimal number 1: "); 
    scanf("%llX", &hex1); 
    printf("hexadecimal number 2: "); 
    scanf("%llX", &hex2); 

    hexSum = hex1 + hex2; 
    hexDiff = hex1 - hex2; 
    
    printf("Their sum is %llX\n", hexSum);
    printf("Their difference is %llX\n", hexDiff);
}
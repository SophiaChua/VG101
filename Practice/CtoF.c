#include <stdio.h>

int main()
{
    int F;
    int C;    

    for (C = -20; C <= 40; C += 10)
    {
        F = (C * 9/5) + 32;
        printf("%4d", F);
    }
    return 0; 
}



#include <stdio.h>

int main(){
    double x; 
    int sign; 

    scanf("%lf", &x);

    if (x == 0)
        sign = 0; 
    else if (x > 0)
        sign = 1; 
    else if (x < 0)
        sign = -1; 

    printf("%d\n", sign);
}
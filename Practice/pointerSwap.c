#include <stdio.h>

int main()
{
    int x, y, *px, *py; 

    printf("x: "); 
    scanf("%d", &x);
    printf("y: ");
    scanf("%d", &y); 

    px = &x;
    py = &y; 
}
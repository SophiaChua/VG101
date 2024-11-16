#include <stdio.h>

int main()
{
    char str[256];
    scanf("%[^\n]%*c", str);  // ask for the user input
    printf("%s\n", str);  // output
    return 0;
}
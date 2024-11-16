#include <stdio.h>

int main()
{

    FILE *fp; 
    char input[120];
    
    fp = fopen("commands.txt", "r");
    
    while(fgets(input, 120, fp) != NULL)
    {
        printf("%s", input); 
    }
    
    fclose(fp);

    return 0; 

}
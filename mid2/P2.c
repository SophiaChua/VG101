#include <stdio.h>
#include <string.h>

int main(){
    char str[256] = ""; 
    int sum; 

    scanf("%s", str);
    
    for (int i = 0; i < strlen(str); i++){
        if (str[i] >= 'a' && str[i] <= 'z')
            sum += str[i]; 
        else if (str[i] >= '0' && str[i] <= '9')
            continue; 
    }

    printf("%d\n", sum); 
}
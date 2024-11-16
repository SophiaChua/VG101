#include <stdio.h>
#include <string.h>

void upper(char *str){
    for (int i = 0; i < strlen(str); i++){
        if (str[i] >= 'a' && str[i] <= 'z'){
            str[i] -= 32;
        }
    }
}

int main(){
    char str[256]; 
    int a = 1; 

    scanf("%s", str); 

    if (str[0] == '0' && str[1] == 'x' || str[1] == 'X'){
        strcpy(str, str+2);
    }

    upper(str); 
    //printf("%s\n", str); 

    for (int i = 0; i < strlen(str); i++){
        for (int j = i + 1; j < strlen(str); j++){
            if (str[i] == str[j]){
                a = 0; 
            }
        }
    }

    printf("%d\n", a); 
}
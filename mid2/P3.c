#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int check(int num){
    int r, digitSum = 0; 

    if (num >= 10){
        while (num != 0){
            r = num % 10; 
            num = num / 10; 
            digitSum = digitSum + r; 
        }
        check(digitSum); 
    }
    else if (num < 10){
        return digitSum; 
    }

    return digitSum; 
}

int main(){
    char str[256]; 
    int digitSum = 0, num, sign = 1, i = 0; 

    scanf("%s", str); 

    if (str[0] == '-'){
        sign = -1;  
        i++;
    }
        
    for (i; i < strlen(str); i++){
        num = str[i] - '0'; 
        digitSum += num; 
    }

    digitSum = check(digitSum) * sign; 

    printf("%d\n", digitSum);
}
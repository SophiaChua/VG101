#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// You can include libraries you need

// You can write other custom functions
typedef struct {
    char name[256]; 
    int grade; 
} student; 

// hw7 - finish this function
void sortscores(char str[]) {
    student s[10];
    char *token; 
    char hold[256], buffer[256]; 
    int temp;
    int i = 0, j = 0; 

    token = strtok(str, " "); 
    strcpy(s[i++].name, token); 

    while (token != NULL)
    {
        token = strtok(NULL, " "); 
        s[j++].grade = atoi(token); 
        token = strtok(NULL, " "); 
        if (token != NULL)
            strcpy(s[i++].name, token); 
    }

    //sort 
    for (int n = 0; n < j; n++){
        for (int b = n + 1; b < j; b++){
            if (s[n].grade < s[b].grade)
            {
                temp = s[n].grade;
                s[n].grade = s[b].grade; 
                s[b].grade = temp; 
                strcpy(hold, s[n].name); 
                strcpy(s[n].name, s[b].name); 
                strcpy(s[b].name, hold); 
            }
        }
    }

    //print
    strcpy(str, ""); 
    for (int m = 0; m < j; m++)
    {
        sprintf(buffer, "%s %d ", s[m].name, s[m].grade); 
        strcat(str, buffer); 
    }
}

// Do NOT change the following lines of code!!!
int main() {
    char str[256];
    scanf("%[^\n]%*c", str);  // ask for the user input
    sortscores(str);
    printf("%s\n", str);  // output
    return 0;
}

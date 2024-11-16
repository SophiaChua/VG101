#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char first[1000][256];
    char last[1000][256]; 
    int ID[1000];  
}students; 

int main(){

    students s[256];
    char in[256]; 
    char *token; 
    FILE *fp; 
    int i = 0, j = 0, n = 0; 

    fp = fopen("P5.txt", "r"); 

    while(fgets(in, 256, fp)){
        token = strtok(in, " "); 
        strcpy(s.first[i++], token); 

        while (token != NULL){
            token = strtok(NULL, " ");
            strcpy(s.last[j++], token); 
            token = strtok(NULL, " "); 
            if (token != NULL)
                s.ID[n++] = atoi(token); 
        }
    }

    //sort

    int temp; 
    char hold1[100], hold2[100]; 

    for (int k = 0; k < n-1; k++){
        for (int m = 0; m < n-1-k; m++){
            if (s.ID[m] > s.ID[m+1]){
                temp = s.ID[m]; 
                s.ID[m] = s.ID[m+1]; 
                s.ID[m+1] = temp; 
                strcpy(hold1, s.first[m]); 
                strcpy(s.first[m], s.first[m+1]); 
                strcpy(s.first[m+1], hold1); 
                strcpy(hold2, s.last[m]); 
                strcpy(s.last[m], s.last[m+1]); 
                strcpy(s.last[m+1], hold2); 
            }
        }
    }

    fclose(fp); 
    char buffer[100]; 
    for (int g = 0; g < n; g++){
        sprintf(buffer, "%d", s.ID[g], ); 
        strcat()
    }
    printf("%-12d %20s %20s\n", s.ID, s.first, s.last);
}
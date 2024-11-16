#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[100]; 
    int grade; 
} student;

int main(){
    student sList[10]; 

    strcpy(sList[0].name, "Wesley"); 
    sList[0].grade = 100; 
    strcpy(sList[1].name, "Ethann"); 
    sList[1].grade = 99; 
    strcpy(sList[2].name, "Sophia"); 
    sList[2].grade = 88; 

    for (int j = 0; j < 3; j++)
        printf("%s %d\n", sList[j].name, sList[j].grade); 
}

#include <iostream>
#include <fstream>

using namespace std; 

int main() {

    int num = 0; 
    char ch; 
    char prev = 'x'; 

    ifstream in("1.in"); 

    while(in) {
        in.get(ch); 
        if (ch == ' ' && prev != ' ' && prev != '\n') {
            num++; 
        }
        else if (ch == '\n' && prev != '\n' && prev != ' ') {
            num++; 
        }
        prev = ch; 
    }

    num++; //to account for the last word //deduction of (-2) because the program didn't count the last word

    cout << num << endl; // num is the total number of words in P4.txt

    in.close();
}
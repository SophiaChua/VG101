#include <iostream>
#include <string>
#include <algorithm>

using namespace std; 

int main ()
{
    int N = 0;
    string str, temp; 
    bool neg = false; 

    cin >> N; // N is a given integer

    if (N < 0) {
        N *= -1; 
        neg  = true; 
    }

    temp = to_string(N); 
    int count = 3, n = 0; //variable "n" is unused (general deduction: -2)

    for (auto it = temp.crbegin(); it != temp.crend(); it++) {
        if (count != 0) {
            str.push_back(*it); 
            count--; 
        }
        else if (count == 0) {
            it--; 
            str.push_back(','); 
            count = 3; 
        }
    }

    if (neg) {
            str.push_back('-'); 
    }

    reverse(str.begin(), str.end()); 

    cout << str << endl; // str is the string that stores the digits with thousand separators

    return 0; 
}
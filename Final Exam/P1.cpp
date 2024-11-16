#include <iostream>

using namespace std; 

int main() 
{
    
    int N = 0, result = 0; 
    
    cin >> N; // N is an integer

    for (int square = 1; square*square <= N; square++) 
    {
        result += square*square; 
    }

    cout << result << endl; // result is the sum of interest

    return 0; 
}
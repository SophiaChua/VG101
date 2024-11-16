#include <iostream>
using namespace std; 

int square(int a)
{
    return a*a; 
}

double square(double b)
{
    return b*b; 
}

int main()
{
    int x = 2; 
    double y = 1.1; 
    cout << "x^2 = " << square(x) << endl; 
    cout << "y^2 = " << square(y) << endl;
    return 0;  
}



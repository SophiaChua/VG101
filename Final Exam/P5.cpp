#include <iostream>

using namespace std; 

int gcd(int b, int d) {
    
    if (b == 0)
        return d; 

    return gcd(d%b, b); 
}

void simplify(int& q, int& p) {
    
    int common_factor = gcd(p, q); 

    if (common_factor < 0) {
        common_factor *= -1; 
    }

    p = p / common_factor;
    q = q / common_factor; 

}

int main() {
    int a, b, c, d, p, q; 

    cin >> a >> b >> c >> d; // a/b is the first number, and c/d is the second number

    q = gcd(b, d); 
    q = (b * d) / q; 

    p = a * (q / b) + c * (q / d); 

    simplify(q, p); 

    if (p == 0) {
        q = 1; 
    }

    if (p < 0 || q < 0) {
        if (p > 0)
            p *= -1; 
        else if (q < 0)
            q *= -1; 
    }

    cout << p << ' ' << q << endl; // p/q = a/b + c/d
}
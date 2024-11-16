#include <iostream>
using namespace std;

// you need to implement/add necessary member functions
class Vector3D
{
public:
    // do NOT change the following member functions
    double getx() const { return x; }
    double gety() const { return y; }
    double getz() const { return z; }

    // task 1: implement member functions for the three operators such that
    //         you can use +, - and * with this class
    Vector3D operator-(const Vector3D& v) // subtraction
    {
        // fill in implementation here
        Vector3D temp; 
        temp.x = x - v.x; 
        temp.y = y - v.y;
        temp.z = z - v.z;

        return temp;  

    }

    Vector3D operator+(const Vector3D& v) // addition
    {
        // fill in implementation here
        Vector3D temp; 
        temp.x = x + v.x; 
        temp.y = y + v.y;
        temp.z = z + v.z;

        return temp;  
    }

    double operator*(const Vector3D& v) // inner product
    {
        // fill in implementation here
        Vector3D temp; 
        return (x * v.x + y * v.y + z * v.z); 

    }

    // task 2: implement proper functions to correctly initialize objects
    Vector3D () {
        x = 1; 
        y = 1; 
        z = 1; 
    }

    Vector3D (double x_in, double y_in, double z_in) {
        x = x_in; 
        y = y_in; 
        z = z_in;
    }
    

private: // do NOT change this keyword
    double x; // do NOT change data member
    double y; // do NOT change data member
    double z; // do NOT change data member
};

// do NOT need to modify the following function, which only takes care of output
ostream& operator<<(ostream& out, const Vector3D& v)
{
    out << "(" << v.getx() << ", " << v.gety() << ", " << v.getz() << ")";
    return out;
}

////////////////////////////////////////////////
// YOU DON'T NEED TO CHANGE THE FOLLOWING CODE
int main()
{
    Vector3D v1, v2(1.0, 1.0, 3.0), v3(-1.0, 3.0, 2.0); // v1 is vector (1,1,1)
    cout << "v2 - v1: " << v2 - v1 << endl; // do NOT change this
    cout << "v2 + v3: " << v2 + v3 << endl; // do NOT change this
    cout << "v2 * v3: " << v2 * v3 << endl; // do NOT change this
    return 0;
}

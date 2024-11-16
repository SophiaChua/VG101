// Note: add additional header files if needed
#include <iostream>

using namespace std;

// HW8 - please fill in the codes in the class
class MySpacetime {
    double x, y, z, ct;

public:
    MySpacetime(double _x = 0, double _y = 0, double _z = 0, double _ct = 0)  // fill in this function
    {
        x = _x; 
        y = _y;
        z = _z;
        ct = _ct; 
    }
    double Interval(const MySpacetime& st2)  // fill in this function
    {              
        // please change the following codes in the function
        return (st2.x - x)*(st2.x - x) + (st2.y - y)*(st2.y - y) + (st2.z - z)*(st2.z - z) - (st2.ct - ct)*(st2.ct - ct);
    }
};

// Note: DON'T CHANGE THE FOLLOWING CODES
int main() {
    double x, y, z, ct;

    cin >> x >> y >> z >> ct;  // input the coordinates of the first spacetime event
    MySpacetime st1(x, y, z, ct);
    cin >> x >> y >> z >> ct;  // input the coordinates of the second spacetime event
    MySpacetime st2(x, y, z, ct);
    cout << st1.Interval(st2);  // output the interval

    return 0;
}

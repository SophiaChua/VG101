// note: add additional header files if needed
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

///////////////////////////////
// note: please fill in the codes as instructed

// problem 1 - please fill in the codes
int P1(int N)
{// feel free to change the following codes in the function
    int S = 0;
    return S;
}

// problem 2 - please fill in the codes
void P2()
{
}

// problem 3 - please fill in the codes
// you need to add necessary member variables and fill in the provided member functions
class P3
{
public:
    P3() // constructor with no input arguments. By default, the point is (x, y, z) = (0, 0, 0);
    {
    }
    P3(double xx, double yy, double zz) // constructor with 3 numbers to initialize the point to be (xx, yy, zz)
    {
    }
    // calculate the distance between the current point with another point pt2
    double Distance(const P3& pt2)
    {// feel free to change the following codes in the function
        double distance = 0;
        return distance;
    }
};

// problem 4 - please fill in the codes
void P4()
{
}
// problem 5 - please fill in the codes
void P5()
{
}

////////////////////////////////////////////////
// YOU DON'T NEED TO CHANGE THE FOLLOWING CODES
// to test your program, run the file and input the problem number
// as instructed
int main(int argc, char** argv)
{
    int n = 0; // problem number
    if (argc == 1)
    {
        cout << "Input problem number (1-5): ";
        cin >> n;
        cin.ignore(); // ignore the rest of stdin buffer
    }
    else if (argc == 2)
    {
        if (argv[1][1] != '\0') {cout << "Invalid argument!" << endl; return -1;}
        switch(argv[1][0])
        {
            case '1': n = 1; break;
            case '2': n = 2; break;
            case '3': n = 3; break;
            case '4': n = 4; break;
            case '5': n = 5; break;
            default: cout << "Invalid argument!" << endl; return -1;
        }
    }
    cout << "Run problem " << n << endl;
    if (n == 1)
    {
        // testing codes
        cout << "P1(-1) = " << P1(-1) << endl;
        cout << "P1(5) = " << P1(5) << endl;
        cout << "P1(8) = " << P1(8) << endl;
    }
    else if (n == 2) P2();
    else if (n == 3)
    {
        // testing codes
        P3 pt1, pt2(1, 0, 0), pt3(0, 1, 0), pt4(1, 1, 1);
        cout << "distance between pt1 and pt2 = " << pt1.Distance(pt2) << endl;
        cout << "distance between pt2 and pt3 = " << pt2.Distance(pt3) << endl;
        cout << "distance between pt3 and pt4 = " << pt3.Distance(pt4) << endl;
    }
    else if (n == 4) P4();
    else if (n == 5) P5();
    return 0;
}

// note: add additional header files if needed
#include <iostream>

using namespace std;

// problem 4 - please fill in the codes in the class
// you need to add necessary member variables and member functions
class MySpacetime 
{
};

// note: DON'T CHANGE THE FOLLOWING CODES
int main() {
	double x, y, z, ct;

	cout << "Please input the coordinates of spacetime events:" << endl;
	cout << "First event: ";
	cin >> x >> y >> z >> ct;
	MySpacetime st1(x, y, z, ct);
	cout << "Second event: ";
	cin >> x >> y >> z >> ct;
	MySpacetime st2(x, y, z, ct);
	cout << "The interval between st1 and st2 is: " << st1.Interval(st2) << endl;
	return 0;
}


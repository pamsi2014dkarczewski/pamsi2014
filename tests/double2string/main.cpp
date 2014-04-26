#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;
int main()
{
	double d=1.12345678901234567890123456789012345678901234567890;
	cout << d << endl;
	stringstream str;
	str << fixed << setprecision( 55 ) << d;
	string s = str.str();
	cout << s;
	return 0;
}
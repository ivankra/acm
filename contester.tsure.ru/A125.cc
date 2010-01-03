#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int main()
{
	long long n;
	cin >> n;

	if (n%3 == 0)
		cout << "3 " << n/3 << endl;
	else if (n == 4)
		cout << "2 2" << endl;
	else if (n%3 == 1)
		cout << "2 2 3 " << (n-4)/3 << endl;
	else if (n == 2)
		cout << "2 1" << endl;
	else
		cout << "2 1 3 " << (n-2)/3 << endl;
}

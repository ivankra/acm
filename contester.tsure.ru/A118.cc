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
	string s;
	cin >> s;

	int n = s.size();
	int m = n / 5;
	for (int i = 0; i < m; i++)
		for (int j = i; j < n; j += m)
			cout << s[j];
	cout << endl;
}

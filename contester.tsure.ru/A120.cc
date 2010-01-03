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
	getline(cin, s);

	reverse(s.begin(), s.end());

	string t = s;
	for (int i = 2; i+4 <= s.size(); i += 6) {
		t[i] = s[i+2];
		t[i+1] = s[i];
		t[i+2] = s[i+3];
		t[i+3] = s[i+1];
	}
	cout << t << endl;
}

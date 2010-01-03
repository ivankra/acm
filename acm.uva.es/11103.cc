#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

int main()
{
	string s;
	while (cin >> s && s != "0") {
		string N, O, V;
		for (int i = 0; i < (int)s.size(); i++) {
			if (s[i] == 'N') N += s[i];
			if (isupper(s[i]) && s[i] != 'N') O += s[i];
			if (islower(s[i])) V += s[i];
		}

		if (V.size() == 0) {
			cout << "no WFF possible" << endl;
		} else {
			int s = min(O.size(), V.size()-1);
			cout << N << O.substr(0, s) << V.substr(0, s+1) << endl;
		}
	}
}

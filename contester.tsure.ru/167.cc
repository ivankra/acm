#include <iostream>
using namespace std;

int main()
{
	string s;
	cin >> s;

	int best = 0;
	for (int i = 0; i <= (int)s.size(); i++) {
		int res = 1;
		for (int k = 0; k < i; k++)
			res *= s[k]-'0';

		if (i == (int)s.size()) {
			best = max(best, res);
		} else if (s[i] != '0') {
			res *= s[i] - '1';
			if (res == 0 && i < (int)s.size()-1) res = 1;

			for (int k = i+1; k < (int)s.size(); k++)
				res *= 9;
			best = max(best, res);
		}
	}

	cout << best << endl;
}

#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	cin >> s;

	int v[1000], n = 0;
	for (int i = 0; i < (int)s.size(); i++) {
		if ('0' <= s[i] && s[i] <= '9') {
			v[n++] = s[i] - '0';
		} else if (s[i] == '+') {
			v[n-2] += v[n-1];
			n--;
		} else if (s[i] == '-') {
			v[n-2] -= v[n-1];
			n--;
		} else if (s[i] == '*') {
			v[n-2] *= v[n-1];
			n--;
		} else if (s[i] == '/') {
			v[n-2] /= v[n-1];
			n--;
		}
	}

	cout << v[n-1] << endl;
}

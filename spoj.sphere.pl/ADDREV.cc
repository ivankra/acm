#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	int N;
	for (cin >> N; N-- > 0;) {
		string s, t;
		cin >> s >> t;

		int c = 0, k = 0;
		for (int i=0; c!=0 || i < (int)max(s.size(), t.size()); i++, c /= 10) {
			if (i < (int)s.size()) c += s[i] - '0';
			if (i < (int)t.size()) c += t[i] - '0';
			if (c%10 == 0 && k == 0) continue;
			cout << (char)(c%10 + '0');
			k++;
		}
		if (k == 0) cout << "0";
		cout << endl;		
	}
}

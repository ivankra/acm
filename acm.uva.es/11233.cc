#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

bool ends(string s, string t) {
	return s.size() >= t.size() && s.substr(s.size() - t.size()) == t;
}

bool vowel(char ch) { return strchr("euioa", ch) != NULL; }

int main() {
	int K, N;
	while (scanf("%d %d", &K, &N) == 2 && K > 0) {
		map<string, string> irreg;
		for (int i = 0; i < K; i++) {
			string a, b;
			cin >> a >> b;
			irreg[a] = b;
		}

		string s;
		while (N-- > 0 && cin >> s) {
			int m = s.size();
			if (irreg.count(s) != 0) {
				cout << irreg[s] << endl;
			} else if (m >= 2 && !vowel(s[m-2]) && s[m-1] == 'y') {
				cout << s.substr(0, m-1) + "ies" << endl;
			} else if (s[m-1] == 'o' || s[m-1] == 's' || s[m-1] == 'x' || ends(s, "ch") || ends(s, "sh")) {
				cout << s << "es" << endl;
			} else {
				cout << s << "s" << endl;
			}
		}
	}
}

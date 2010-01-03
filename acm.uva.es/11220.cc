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
using namespace std;

int main() {
	string line;

	getline(cin, line);
	int T = atoi(line.c_str());

	getline(cin, line);

	for (int cs = 1; cs <= T; cs++) {
		if (cs != 1) printf("\n");
		printf("Case #%d:\n", cs);

		while (getline(cin, line) && line != "") {
			string word, res = "";
			istringstream is(line);
			for (int i = 0; is >> word;) {
				if (word.size() >= 1+i)
					res += word[i++];
			}
			printf("%s\n", res.c_str());
		}
	}
}

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
	int T;
	scanf("%d", &T);

	long long a, b;
	for (int cs = 1; cs <= T && scanf("%lld %lld", &a, &b) == 2; cs++) {
		string s = "";
		for (;;) {
			if (a == 0 && b == 0) break;

			int bit = (a + b) % 2 == 0 ? 0 : 1;
			a -= bit;

			long long a1 = (a - b) / (-2);
			long long b1 = (a + b) / (-2);
			a = a1; b = b1;

			s += (char)('0'+bit);
		}

		if (s == "") s = "0";
		reverse(s.begin(), s.end());
		printf("Case #%d: %s\n", cs, s.c_str());
	}
}

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
	int N;
	cin >> N;

	long long a = 210, b = 297;
	int u = 0, v = 0;
	for (int i = 0; i < N; i++) {
		while (a % 2 == 0 && b % 2 == 0) { a /= 2; b /= 2; }

		assert(a != b);
		if (a < b) {
			u++;
			a *= 2;
		} else {
			v++;
			b *= 2;
		}
	}

	long long res = ((1LL<<u)-1) + ((1LL<<v)-1);
	cout << res << endl;
}

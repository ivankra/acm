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
	int T;
	scanf("%d", &T);

	int x, y;
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d / %d", &x, &y);

		int g = __gcd(x, y);
		x /= g; y /= g;

		if (x < y) {
			printf("%d/%d\n", x, y);
		} else {
			int n = x / y;
			x %= y;
			if (x == 0) printf("%d\n", n);
			else printf("%d %d/%d\n", n, x, y);
		}
	}
}

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

int solve(int a, int b, int c)
{
	if (a > b) swap(a, b);

	{
		int g = __gcd(a, b);
		if (c % g != 0) return -1;
		a /= g; b /= g; c /= g;
	}

	if (c > a && c > b) return -1;

	int x = 0, y = 0, n = 0;
	do {
		if (x == a) x = 0;
		else if (y == 0) y = b;
		else { int t = min(a-x, y); y -= t; x += t; }
		n++;
	} while (x != 0 || y != 0);

	x = y = 0;
	int res = n;
	for (int i = 0; i < n; i++) {
		if (x == c || y == c)
			res = min(res, min(i, n-i));
		if (x == a) x = 0;
		else if (y == 0) y = b;
		else { int t = min(a-x, y); y -= t; x += t; }
	}

	return res;
}

int main()
{
	int T;
	scanf("%d", &T);

	int a, b, c;
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d", &a, &b, &c);
		printf("%d\n", solve(a, b, c));
	}
}

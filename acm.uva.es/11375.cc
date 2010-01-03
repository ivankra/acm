#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
#define foreach(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

int sizes[10] = {6,2,5,5,4,5,6,3,7,6};

struct Big {
	unsigned a[63], n;
	Big() { clear(); }
	void clear() { n = 0; }
	void operator +=(const Big &y) {
		while (n < y.n) a[n++] = 0;

		unsigned c = 0, i;
		for (i = 0; i < y.n; i++) {
			c += a[i] + y.a[i];
			if (c >= 1000000000) {
				a[i] = c - 1000000000;
				c = 1;
			} else {
				a[i] = c;
				c = 0;
			}
		}

		if (c != 0) {
			while (i < n) {
				++a[i];
				if (a[i] == 1000000000) {
					a[i] = 0;
					i++;
				} else {
					break;
				}
			}
			if (i == n) a[n++] = 1;
		}
	}

	void print() {
		if (n == 0) {
			printf("0\n");
		} else {
			for (int i = n-1; i >= 0; i--)
				printf(i==n-1 ? "%u" : "%.9u", a[i]);
			printf("\n");
		}
	}
};

Big f[2048], ans[2048];
Big one;

int main()
{
	one.a[0] = 1; one.n = 1;

	f[0] = one;

	for (int n = 1; n <= 2000; n++) {
		for (int d = 0; d <= 9; d++) {
			if (sizes[d] <= n) f[n] += f[n - sizes[d]];
		}

		ans[n] = ans[n-1];
		for (int d = 1; d <= 9; d++) {
			if (sizes[d] <= n) ans[n] += f[n - sizes[d]];
		}

		if (n == 6) ans[n] += one;
	}

	int N;
	while (scanf("%d", &N) == 1 && N >= 1) {
		ans[N].print();
	}
}

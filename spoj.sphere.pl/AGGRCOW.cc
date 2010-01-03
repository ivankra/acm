#include <cstdio>
#include <algorithm>
using namespace std;

int x[131072], n, c;

int check(int d)
{
	int i, z=x[0]+d, r=c-1;

	x[n] = 0x7fffffff;
	for (i = 1; r > 0; r--) {
		while (x[i] < z) i++;
		if (i >= n) return 0;
		z = x[i++] + d;
	}

	return 1;
}

int main()
{
	int i, j, T;

	for (scanf("%d", &T); T-- > 0 && scanf("%d %d", &n, &c) == 2;) {
		for (i = 0; i < n; i++) scanf("%d", &x[i]);
		sort(x, x+n);

		for (i = 0, j = x[n-1]-x[0]; i < j;) {
			int c = (i + j + 1) / 2;
			if (check(c)) i = c; else j = c-1;
		}

		printf("%d\n", i);
	}

	return 0;
}

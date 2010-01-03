#include <cstdio>
#include <algorithm>
using namespace std;

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x%y); }

char a[1048576];

int main()
{
	int lim;
	while (scanf("%d", &lim) == 1) {
		int r1 = 0, r2 = 0;

		fill(a, a+lim+1, 0);

		for (int m = 1; (m * m) < lim; m++)
		for (int n = 1 + (m & 1); n < m; n += 2) {
			int x = 2 * m * n;
			if (x > lim) break;

			int y = m * m - n * n;
			if (y <= 0) break;

			if (x > y) swap(x, y);

			int z = m * m + n * n;
			if (z > lim) break;

			if (gcd(m, n) != 1) continue;

			// (x,y,z) is a primitive pyth. triple
			r1++;

			for (int t = 1; (z * t) <= lim; t++)
				a[x*t] = a[y*t] = a[z*t] = 1;
		}

		for (int x = 1; x <= lim; x++)
			if (a[x] == 0) r2++;

		printf("%d %d\n", r1, r2);
	}
}

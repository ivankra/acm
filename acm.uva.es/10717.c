#include <stdio.h>

long long a[256], h, r1, r2;
int n;

long long gcd(long long a, long long b)
{
	int k;

	for (k = 0; (a & 1) == 0 && (b & 1) == 0; k++, a >>= 1, b >>= 1);

	for (;;) {
		if (a == 0) return (b << k);
		if (b == 0) return (a << k);

		while ((a & 1) == 0) a >>= 1;
		while ((b & 1) == 0) b >>= 1;

		if (a > b)
			a -= b;
		else
			b -= a;
	}
}

long long lcm(long long a, long long b)
{
	return (a * b / gcd(a, b));
}

void solve()
{
	int x, y, z, w;
	long long l1, l2, l, t;

	for (r1 = r2 = 0, x = 3; x < n; x++) {
		for (y = 0; y < x; y++) {
			l1 = lcm(a[x], a[y]);
			for (z = 0; z < y; z++) {
				l2 = lcm(l1, a[z]);
				for (w = 0; w < z; w++) {
					l = lcm(l2, a[w]);
					t = (h / l) * l;

					if (t == h) {
						r1 = r2 = h;
						return;
					}

					if (t > r1) r1 = t;
					t += l;
					if (r2 == 0 || t < r2) r2 = t;
				}
			}
		}
	}
}

int main()
{
	int i, t;

	while (scanf("%d %d", &n, &t) == 2 && n >= 4) {
		for (i = 0; i < n; i++)
			scanf("%lld", &a[i]);

		while (t-- > 0 && scanf("%lld", &h) == 1) {
			solve();
			printf("%lld %lld\n", r1, r2);
		}
	}

	return 0;
}

#include <cstdio>
#include <cstring>

int a[2000100], n;

int main()
{
	scanf("%d", &n);

	memset(a, 0xff, (n+10)*sizeof(int));
	for (int p = 2; p <= n; p++) {
		if (a[p] >= 0) continue;

		for (int q = p; q <= n; q += p) {
			if (a[q] < 0)
				a[q] = p - 1;
			else
				a[q] *= p - 1;
		}

		if (p >= 1420) continue;

		for (long long m = p * p; m <= (long long)n; m *= p)
			for (int t = m; t <= n; t += m)
				a[t] *= p;
	}

	long long cnt = 0;
	for (int den = 2; den <= n; den++)
		cnt += (long long)a[den];

	for (int g = 0;; g++) {
		if (cnt <= (1LL << g)) {
			printf("%d\n", g);
			break;
		}
	}
}

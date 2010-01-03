#include <cstdio>
#include <cstring>

char sieve[100010], small[65536];

int main()
{
	int t, n, m;

	memset(small, 0, sizeof(small));
	for (int p = 2; p < 256; p++) {
		if (small[p]) continue;
		for (int q = p*p; q < 65536; q += p) small[q] = 1;
	}
	
	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &m, &n) == 2;) {
		memset(sieve, 0, sizeof(sieve));
		for (int p = 2; p*p <= n; p++) {
			if (small[p]) continue;

			int q = (m / p) * p;
			while (q < m || q <= p) q += p;

			for (; q <= n; q += p)
				sieve[q-m] = 1;
		}

		for (int i = m; i <= n; i++)
			if (i >= 2 && sieve[i-m] == 0) printf("%d\n", i);

		if (t > 0) printf("\n");
	}
}

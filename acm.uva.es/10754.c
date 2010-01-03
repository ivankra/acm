#include <stdio.h>
#include <string.h>

typedef long long matrix_t[32][32];

long long mod;

static void mul(matrix_t a, matrix_t b, int n)
{
	static matrix_t t;
	register int i, j, k;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (t[i][j] = 0, k = 0; k < n; k++)
				t[i][j] = (t[i][j] + a[i][k] * b[k][j]) % mod;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			a[i][j] = t[i][j];
}

void power(matrix_t z, int p, int n)
{
	static matrix_t a;
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			a[i][j] = z[i][j];

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			z[i][j] = (i == j) ? 1 : 0;

	for (; p > 0; p >>= 1) {
		if (p & 1)
			mul(z, a, n);

		if (p > 1)
			mul(a, a, n);
	}
}

long long solve()
{
	static long long a[32], x;
	static matrix_t m;
	int i, j, n, z;

	scanf("%d %lld %d", &n, &mod, &z);

	for (i = 0; i <= n; i++)
		for (j = 0; j <= n; j++) m[i][j] = 0;

	for (i = 0; i <= n; i++) {
		scanf("%lld", &x);
		m[0][i] = (x < 0) ? (mod - ((-x) % mod)) : (x % mod);
		m[0][i] %= mod;
	}

	for (i = 0; i < n; i++) {
		scanf("%lld", &x);
		a[i] = (x < 0) ? (mod - ((-x) % mod)) : (x % mod);
		a[i] %= mod;
	}

	if (z < n)
		return a[z];

	if (n == 0)
		return m[0][0];

	for (i = 1; i < n; i++)
		m[i][i - 1] = 1;
	m[n][n] = 1;

	power(m, z - n + 1, n + 1);

	for (x = m[0][n], i = 0; i < n; i++)
		x = (x + m[0][i] * a[n - i - 1]) % mod;

	return x % mod;
}

int main()
{
	int t;

	for (scanf("%d", &t); t-- > 0;)
		printf(t ? "%lld\n\n" : "%lld\n", solve() % mod);

	return 0;
}

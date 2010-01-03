#include <stdio.h>

int a[128], n;

int solve()
{
	static int z1[65536], z2[65536], g[65536], id = 42;
	static char p[128][65536];
	int i, j, k, *x, *y;

	z1[0] = a[0]; z1[1] = 65536;
	for (i = 1; i < n; i++) {
		if (i & 1)
			x = z1, y = z2;
		else
			x = z2, y = z1;

		for (id++; x[0] <= 32768; x++) {
#define CHECK(op,opc) \
	j = x[0] op a[i]; \
	if (j <= 32000 && j >= -32000 && g[j + 32768] != id) \
		*y++ = j, p[i][j + 32768] = opc, g[32768 + j] = id;
			CHECK(+, '+');
			CHECK(-, '-');
			CHECK(*, '*');
			if ((x[0] % a[i]) == 0) CHECK(/, '/');
#undef CHECK
		}

		y[0] = 65536;
	}

	if (g[32768 + a[n]] != id)
		return 1;

	for (k = a[n], i = n; i-- > 1;) {
		z1[i] = j = p[i][k + 32768];
		if (j == '/')
			k *= a[i];
		else if (j == '*')
			k /= a[i];
		else if (j == '+')
			k -= a[i];
		else
			k += a[i];
	}

	printf("%d", a[0]);
	for (i = 1; i < n; i++)
		printf("%c%d", z1[i], a[i]);
	printf("=%d\n", a[n]);

	return 0;
}

int main()
{
	int i, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);
		scanf("%d", &a[n]);
		if (solve()) printf("NO EXPRESSION\n");
	}

	return 0;
}

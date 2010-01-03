#include <stdio.h>

int read(int, char *, int);

int init[16], coef[16], d, n, m;

static void mmul(int r[16][16], int a[16][16], int b[16][16])
{
	static int t[16][16];
	int i, j, k;

	for (i = 0; i < d; i++)
		for (j = 0; j < d; j++)
			for (t[i][j] = 0, k = 0; k < d; k++)
				t[i][j] += a[i][k] * b[k][j];

	for (i = 0; i < d; i++)
		for (j = 0; j < d; j++)
			r[i][j] = t[i][j];
}

int solve_d3logn()
{

/*	A = I * M^n*/


	return 0;
}

static int solve_dn()
{
	static int a[32];
	int i, t;

printf("[O(dn) chosen] ");

	for (i = 0; i < d; i++)
		a[i] = init[d - i];

	for (;;) {
		for (t = 0, i = 0; i < d; i++)
			t = (t + a[i] * coef[i]) % m;

		if (n-- <= 1)
			return t;

		for (i = d - 2; i >= 0; i--)
			a[i + 1] = a[i];
		a[0] = t;
	}
}

int power_log(int x)
{
	int r;
	for (r = 0; x > 0; x >>= 1)
		r += 1 + (x & 1);
	return r;
}

int main()
{
	static char buf[1048576];
	static int isdig[256];
	char *inp;
	int i, j;

	for (i = 0; i < 256; i++)
		isdig[i] = ('0' <= i && i <= '9');

	buf[read(0, inp = buf, sizeof(buf))] = '\0';

#define READ(x) \
	{ while(!isdig[*inp]) inp++; \
	  for (x = *inp++ - '0'; isdig[*inp];) x = x * 10 + *inp++ - '0'; }

	for (;;) {
		READ(j); if (j == 0) break; d = j;
		READ(j); n = j;
		READ(j); m = j;

		for (i = 0; i < d; i++) {
			READ(j);
			coef[i] = j % m;
		}

		for (i = 1; i <= d; i++) {
			READ(j);
			init[i] = j % m;
		}

		if (n <= d) {
			printf("%d\n", init[n]);
			continue;
		}

printf("%d\n", solve_dn());
continue;

		if (n > 16777216) {
			printf("%d\n", solve_d3logn());
			continue;
		}

		n -= d;

		i = 2 * power_log(n) * d * d * (3 * d + 1);
		i -= 2 * d * n;

printf("[%d] ", i);

		if (i < 0)
			printf("%d\n", solve_d3logn());
		else
			printf("%d\n", solve_dn());
	}

	return 0;
}

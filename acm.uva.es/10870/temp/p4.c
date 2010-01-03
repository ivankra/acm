#include <stdio.h>
#include <string.h>

int read(int, char *, int);

int init[16], coef[16], d, ind, m;

static void square(int r[16][16], int a[16][16])
{
	int i, j, k;

	for (i = 0; i < d; i++)
		for (j = 0; j < d; j++)
			for (r[i][j] = 0, k = 0; k < d; k++)
				r[i][j] = (r[i][j] + a[i][k] * a[k][j]) % m;
}

static void zmul(int r[16][16], int a[16][16])
{
	int i, j, k;

/*
	memset(z, 0, sizeof(z));
	for (i = 0; i < d; i++) z[0][i] = coef[i];
	for (i = 1; i < d; i++) z[i][i - 1] = 1;

     [ c0  c1  c2  ... c_d-1  c_d ][ a00  a01  a02  ... a_0d]
     [  1                         ][ a10  a11  a12  ... a_1d]
  R= [      1                     ][ ...       [a_ij]       ]
     [          1  ...            ][                        ]
     [                   1        ][ a_d1 a_d2          a_dd]
                    Z                           A
*/
	for (j = 0; j < d; j++)
		for (r[0][j] = 0, k = 0; k < d; k++)
			r[0][j] = (r[0][j] + coef[k] * a[k][j]) % m;

	for (i = 1; i < d; i++)
		for (j = 0; j < d; j++)
			r[i][j] = a[i - 1][j];

/*

	for (i = 0; i < d; i++)
		for (j = 0; j < d; j++)
			for (r[i][j] = 0, k = 0; k < d; k++)
				r[i][j] = (r[i][j] + a[i][k] * b[k][j]) % m;
*/

}

int solve_d3logn()
{
	static int a[2][16][16];
	int i, k, s;

	memset(a, 0, sizeof(a));
	for (i = 0; i < d; i++)
		a[0][i][i] = 1;

	for (i = 0; (ind >> i) > 0; i++);

	for (s = 0;;) {
		if ((ind >> i) & 1) {
			zmul(a[s ^ 1], a[s]);
			s ^= 1;
		}

		if (i-- < 1)
			break;

		square(a[s ^ 1], a[s]);
		s ^= 1;
	}

	for (k = 0, i = 0; i < d; i++)
		k = (k + init[d - i] * a[s][0][i]) % m;

	return k;
}

static int solve_dn()
{
	static int a[32];
	int i, t;

	for (i = 0; i < d; i++)
		a[i] = init[d - i];

	for (;;) {
		for (t = 0, i = 0; i < d; i++)
			t = (t + a[i] * coef[i]) % m;

		if (ind-- <= 1)
			return t;

		for (i = d - 2; i >= 0; i--)
			a[i + 1] = a[i];
		a[0] = t;
	}
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
	{ while(!isdig[(int)*inp]) inp++; \
	  for (x = *inp++ - '0'; isdig[(int)*inp];) x = x * 10 + *inp++ - '0'; }

	for (;;) {
		READ(j); if (j == 0) break; d = j;
		READ(j); ind = j;
		READ(j); m = j;

		for (i = 0; i < d; i++) {
			READ(j);
			coef[i] = j % m;
		}

		for (i = 1; i <= d; i++) {
			READ(j);
			init[i] = j % m;
		}

		if (ind <= d) {
			printf("%d\n", init[ind]);
			continue;
		}

		ind -= d;

		if (ind > 30000)
			printf("%d\n", solve_d3logn());
		else
			printf("%d\n", solve_dn());
	}

	return 0;
}

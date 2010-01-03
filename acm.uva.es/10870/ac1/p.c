#include <stdio.h>
#include <string.h>

int read(int, char *, int);

static int init[16], coef[16], d, ind, m;

#define REF(a,i,j) a[i][j]

static void square(int r[16][16], int a[16][16])
{
	int i, j, k;

	for (i = 0; i < d; i++)
		for (j = 0; j < d; j++)
			for (REF(r,i,j)=0, k = 0; k < d; k++)
				REF(r,i,j) = (REF(r,i,j) + REF(a,i,k) * REF(a,k,j)) % m;
}

static void zmul(int r[16][16], int a[16][16])
{
	int i, j;

	for (j = 0; j < d; j++)
		for (REF(r,0,j) = 0, i = 0; i < d; i++)
			REF(r,0,j) = (REF(r,0,j) + coef[i] * REF(a,i,j)) % m;

	for (i = 1; i < d; i++)
		for (j = 0; j < d; j++)
			REF(r,i,j) = REF(a, i - 1, j);
}

static int solve_d3logn()
{
	static int a[2][16][16];
	int i, k, s;

	memset(a, 0, sizeof(a));
	for (i = 0; i < d; i++)
		REF(a[0],i,i) = 1;

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
		k = (k + init[d - i] * REF(a[s],0,i)) % m;

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
	static char buf[131072];
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

		if (ind > 5000)
			printf("%d\n", solve_d3logn());
		else
			printf("%d\n", solve_dn());
	}

	return 0;
}

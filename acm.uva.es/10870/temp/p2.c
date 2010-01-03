#include <stdio.h>
#include <string.h>

int read(int, char *, int);

int init[16], coef[16], d, ind, m;

static void mmul(int r[16][16], int a[16][16], int b[16][16])
{
	int i, j, k;

	for (i = 0; i < d; i++)
		for (j = 0; j < d; j++)
			for (r[i][j] = 0, k = 0; k < d; k++)
				r[i][j] = (r[i][j] + a[i][k] * b[k][j]) % m;
}

static void square(int r[16][16], int a[16][16])
{
	int i, j, k;

	for (i = 0; i < d; i++)
		for (j = 0; j < d; j++)
			for (r[i][j] = 0, k = 0; k < d; k++)
				r[i][j] = (r[i][j] + a[i][k] * a[k][j]) % m;
}

int solve_d3logn()
{
	static int a[2][16][16], z[16][16];
	int i, k, s;

	memset(a, 0, sizeof(a));
	for (i = 0; i < d; i++)
		a[0][i][i] = 1;

	memset(z, 0, sizeof(z));
	for (i = 0; i < d; i++)
		z[0][i] = coef[i];

	for (i = 1; i < d; i++)
		z[i][i - 1] = 1;

printf("init^T={");for(i=d;i>=1;i--)printf(" %d",init[i]);printf(" }\n");

printf("Z=\n");
for(i=0;i<d;i++){
for(k=0;k<d;k++)printf("%d ",z[i][k]);printf("\n");}

printf("Z^%d=\n",ind);

	for (i = 0; (ind >> i) > 0; i++);

	for (s = 0; i >= 0; i--) {
		square(a[s ^ 1], a[s]);
		s ^= 1;

		if ((ind >> i) & 1) {
			mmul(a[s ^ 1], a[s], z);
			s ^= 1;
		}
	}

for(i=0;i<d;i++){
for(k=0;k<d;k++)printf("%d ",a[s][i][k]);printf("\n");}

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

printf("n=%d d=%d  ind=%d\n", ind, d, ind - d);
		ind -= d;

printf("%d\n", solve_d3logn());

continue;


		if (ind > 16777216) {
			printf("%d\n", solve_d3logn());
			continue;
		}

		for (i = 0, j = ind; j > 0; j >>= 1)
			i += d + (j & 1);
		i = 6 * i * d - 2 * ind;

printf("[%d] ", i);

		if (i < 0)
			printf("%d\n", solve_d3logn());
		else
			printf("%d\n", solve_dn());
	}

	return 0;
}

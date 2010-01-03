#include <stdio.h>
#include <string.h>

int n, p, pat[2048], npat, pmask;
/* p: length of filtering bit strings
   pat[i]: non-zero iff bit string 'i' must be filtered */

/* tab[i][j]: number of possible i-bit strings, ending with p-bit string 'j' */
long long tab[64][2048];

char *bin(int x, int s)
{
	static char buf[128];
	int i;
	
	for (i = 0; i < s; i++)
		buf[i] = ((x >> (s - i - 1)) & 1) + '0';
	buf[i] = '\0';

	return buf;
}

int main()
{
	char s[256];
	int i, j, k, t;
	long long r1, r2;

	for (t = 1; scanf("%d %d", &n, &npat) == 2 && n > 0; t++) {
		memset(pat, 0, sizeof(pat));

		for (i = p = 0; i < npat && scanf(" %[HTht]", s) == 1; i++) {
			for (j = 0, k = 0; s[j]; j++)
				if ((s[j] | 0x20) == 'h')
					k = (k << 1) | 1;
				else
					k <<= 1;

			p = j;
			pat[i] = k;
		}

		if (p > n) {
			printf("Case %d: 1/1\n", t);
			continue;
		}

		pmask = (1 << p) - 1;

		memset(tab, 0, sizeof(tab));
		tab[0][0] = 1;

		for (k = 1; k <= n; k++) {
			for (i = 0; i <= pmask; i++) {
				j = (i << 1) & pmask;
				tab[k][j] += tab[k - 1][i];

				j = ((i << 1) | 1) & pmask;
				tab[k][j] += tab[k - 1][i];
			}

			if (k >= p) {
				for (i = 0; i < npat; i++)
					tab[k][pat[i]] = 0;
			}
		}

#if 1
		printf("\np=%d n=%d\n",p,n);
		for (i = 0; i <= pmask; i++) {
			printf("%s:", bin(i, p));
			for (j = 0; j <= n; j++)
				printf(" %3I64d", tab[j][i]);
			printf("\n");
		}

		printf("restricted:");
		for (i = 0; i < npat; i++)
			printf(" %s", bin(pat[i],p));
		printf("\n");

#endif

		for (i = 0, r1 = 0; i <= pmask; i++)
			r1 += tab[n][i];

		if (r1 == 0) {
			printf("Case %d: 0\n", t);
		} else {
			r2 = (1ULL << n);

			while (r2 > 1ULL && (r1 & 1ULL) == 0ULL)
				r2 >>= 1, r1 >>= 1;

			printf("Case %d: %I64d/%I64d\n", t, r1, r2);
		}
	}

	return 0;
}

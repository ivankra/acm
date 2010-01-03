#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned u_int32_t;
typedef unsigned long long u_int64_t;

char *tab[512], s[1024];
u_int32_t x[128];

#define RADIX 1000000000ULL

int main()
{
	int i, j, p, n, m;
	u_int64_t c;

	for (i = 0; i < 512; i++)
		tab[i] = NULL;

	while (scanf("%d", &n) == 1 && n > 0) {
		if (tab[n] != NULL) {
			printf("%s\n", tab[n]);
			continue;
		}

		/* closed form: (2n)! / (n+1)! */

		x[0] = 1;
		m = 1;

		for (p = n + 2; p <= (n << 1); p++) {
			for (i = 0, c = 0; i < m; i++) {
				c += (u_int64_t)x[i] * (u_int64_t)p;
				if (c >= RADIX) {
					x[i] = (u_int32_t)(c % RADIX);
					c /= RADIX;
				} else {
					x[i] = (u_int32_t)c;
					c = 0;
				}
			}

			if (c != 0)
				x[m++] = (u_int32_t)c;
		}

		sprintf(s, "%u", (unsigned)x[--m]);

		for (j = strlen(s); m-- > 0;) {
			sprintf(s + j, "%.9u", (unsigned)x[m]);
			j += strlen(s + j);
		}

		tab[n] = (char *)malloc(j + 1);
		strcpy(tab[n], s);

		printf("%s\n", tab[n]);
	}

	return 0;
}

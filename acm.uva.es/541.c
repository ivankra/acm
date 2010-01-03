#include <stdio.h>

static int a, n, r[128], c[128];
static int cr, cc, nr, nc;

int main()
{
	register int i, j;

	while (scanf("%d", &n) == 1 && n != 0) {
		for (i = 0; i < n; i++)
			r[i] = c[i] = 0;

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				scanf("%d", &a);
				a &= 1;
				r[i] ^= a;
				c[j] ^= a;
			}
		}

		for (i = 0, nr = 0; i < n; i++) {
			if (r[i]) {
				if (++nr >= 2) break;
				cr = i;
			}
		}

		if (nr >= 2) {
			printf("Corrupt\n");
			continue;
		}

		for (i = 0, nc = 0; i < n; i++) {
			if (c[i]) {
				if (++nc >= 2) break;
				cc = i;
			}
		}

		if (nr == 0 && nc == 0)
			printf("OK\n");
		else if (nr == 1 && nc == 1)
			printf("Change bit (%d,%d)\n", 1+cr, 1+cc);
		else
			printf("Corrupt\n");
	}

	return 0;
}

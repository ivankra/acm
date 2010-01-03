#include <stdio.h>

#define MAXN 65536

int main()
{
	static int a[MAXN], p[MAXN], r[MAXN], n, t;
	static char buf[4096];
	register int i, k, m;

	scanf("%d\n", &t);

	while (t-- > 0) {
		for (n = 0; gets(buf) != NULL;) {
			if (n >= MAXN) { char *p; for (;;) *p++ = 42; }

			if (sscanf(buf, "%d", &a[n]) != 1)
				break;

			for (i = 0, k = -1, m = 0; i < n; i++)
				if (a[i] < a[n] && r[i] > m) m = r[k = i];

			r[n] = m + 1;
			p[n] = k;

			n++;
		}

		for (i = 0, k = 1; k < n; k++)
			if (r[k] > r[i]) i = k;

		for (k = 0; i >= 0; i = p[i])
			r[k++] = a[i];

		printf("Max hits: %d\n", k);
		while (k-- > 0)
			printf("%d\n", r[k]);
		if (t > 0) printf("\n");
	}

	return 0;
}

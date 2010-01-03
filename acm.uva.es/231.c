#include <stdio.h>

#define MAXN 1048576

int main()
{
	static int a[MAXN], d[MAXN], n, t;
	register int i, j;

	for (t = 1;; t++) {
		for (n = 0; scanf("%d", &a[n]) == 1 && a[n] >= 0; n++);

		if (n == 0)
			break;

		for (i = 0; i < n; i++) {
			for (d[i] = 1, j = 0; j < i; j++)
				if (a[j] >= a[i] && d[j] >= d[i])
					d[i] = d[j] + 1;
		}

		for (j = d[0], i = 1; i < n; i++)
			if (d[i] > j) j = d[i];

		if (t != 1) printf("\n");
		printf("Test #%d:\n  maximum possible interceptions: %d\n",
			t, j);
	}

	return 0;
}

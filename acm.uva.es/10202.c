#include <stdio.h>
#include <string.h>

static void sort(int a[], int n)
{
	register int i, j, t;

	for (i = 1; i < n; i++) {
		for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
			a[j + 1] = a[j];
		a[j + 1] = t;
	}
}

static int m, n, k, a[16], s[128];
static int found[16][16];

static int try(int r)
{
	int i, j, c, t;

	/*  s[0] = a[0] + a[1]
	    s[1] = a[0] + a[2]
	    s[r] = a[1] + a[2] (guess)

	    s[0] + s[1] - s[r] = 2 a[0]
	    a[1] = s[0] - a[0]
	    a[2] = s[1] - a[0] */

	t = s[0] + s[1] - s[r];
	if (t & 1) return 0;

	a[0] = (t >> 1);
	a[1] = s[0] - a[0];
	a[2] = s[1] - a[0];
	k = 3;                 /* no of discovered numbers */

	/* mark found pairs
	   found[i][j] (with i < j) = has sum a[i] + a[j] been identified? */
	memset(found, 0, sizeof(found));
	found[0][1] = 1;
	found[0][2] = 1;
	found[1][2] = 1;

	for (c = 2; c < m; c++) {
		if (c == r)
			continue;

		/* s[c] = a[i] + a[j], with i < k, j < k
		   or: s[c] = a[0] + a[k] */

		for (i = 0; i < k; i++) {
			for (j = i + 1; j < k; j++) {
				if (!found[i][j] &&
				    s[c] == (a[i] + a[j]))
					break;
			}
			if (j < k) break;
		}

		if (i < k) {
			/* s[c] = a[i] + a[j] */
			found[i][j] = 1;
		} else {
			/* s[c] = a[0] + a[k] */
			if (k >= n) return 0;
			a[k++] = s[c] - a[0];
			found[0][k] = 1;
		}
	}

	return (k == n);
}

int main()
{
	int i;

	while (scanf("%d", &n) == 1) {
		m = (n * (n - 1)) >> 1;

		for (i = 0; i < m; i++)
			scanf("%d", &s[i]);

		sort(s, m);

		for (i = 2; i < m; i++)
			if (try(i)) break;

		if (i >= m) {
			printf("Impossible\n");
		} else {
			for (i = 0; i < n; i++)
				printf(((i + 1) >= n) ? "%d\n" : "%d ", a[i]);
		}
	}

	return 0;
}

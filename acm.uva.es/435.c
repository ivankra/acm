#include <stdio.h>

int party[256], n;

int count(int p)
{
	static int a[4096];
	int i, k, m;

	/* m = total number of votes */
	for (i = 0, m = 0; i < n; i++)
		m += party[i];

	for (a[0] = 1, i = 1; i <= m; i++)
		a[i] = 0;

	for (k = 0; k < n; k++) {
		if (k == p)
			continue;

		for (i = m - party[k]; i >= 0; i--)
			a[i + party[k]] += a[i];
	}

	/* a[i] = the number of coalitions the other parties may form with
	   the total number of votes equal to `i' */

	for (k = 0, i = 0; i <= m; i++) {
		if ((2 * i) <= m &&
		    (2 * (i + party[p])) > m)
			k += a[i];
	}

	return k;
}

int main()
{
	int i, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 0; i < n; i++)
			scanf("%d", &party[i]);

		for (i = 0; i < n; i++)
			printf("party %d has power index %d\n",
			       i + 1, count(i));

		printf("\n");
	}

	return 0;
}

#include <stdio.h>

int a[8], n, inv, r;

void solve(int p)
{
	int i, m;

	for (i = 1; i < n; i++) {
		if (a[i - 1] <= a[i])
			continue;

		m = a[i];
		a[i] = a[i - 1];
		a[i - 1] = m;

		if ((p + 1) < inv)
			solve(p + 1);
		else
			r++;
	
		m = a[i];
		a[i] = a[i - 1];
		a[i - 1] = m;
	}
}

int main()
{
	int i, j, t;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		for (inv = 0, i = 0; i < n; i++)
			for (j = i + 1; j < n; j++)
				if (a[i] > a[j]) inv++;

		r = 0;
		solve(0);

		printf("There are %d swap maps for input data set %d.\n", r, t);
	}

	return 0;
}

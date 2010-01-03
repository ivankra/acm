#include <stdio.h>
#include <math.h>

int a[65536], n;

int recur(int i, int j)
{
	int t;

	if (i < 0 || j < 0 || i >= n || j >= n)
		return 0;

	if (i < j) {
		for (t = 0; j < n; j++)
			if (a[i] > a[j]) t++;
		return t;
	} else {
		/* i > j */
		for (t = 0; j >= 0; j--)
			if (a[i] > a[j]) t++;
		return t;
	}
}

int main(void)
{
	int i, s, c;

	for (c = 1; scanf("%d", &n) == 1 && n > 0; c++) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		for (s = 0, i = 0; i < n; i++) {
			s += recur(i, i + 1);
			s += recur(i, i - 1);
		}

		printf("Case %d: %d\n", c, s);
	}

	return 0;
}

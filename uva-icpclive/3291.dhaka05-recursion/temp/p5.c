#include <stdio.h>
#include <stdlib.h>

int a[65536], n;

/* how many elements of a[] to the right of a[i] are less than a[i]? */
int R(int i)
{
	int t, j;

	for (t = 0, j = i + 1; j < n; j++)
		if (a[j] < a[i]) t++;

	return t;
}

/* how many elements of a[] to the left of a[i] are less than a[i]? */
int L(int i)
{
	int t, j;

	for (t = 0, j = i - 1; j >= 0; j--)
		if (a[j] < a[i]) t++;

	return t;
}

int cmp(const void *p, const void *q)
{
	return *(int *)q - *(int *)p;
}

int main(void)
{
	int i, s, c;

	for (c = 1; scanf("%d", &n) == 1 && n > 0; c++) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		s = -L(0) - R(n-1);

		qsort(a, n, sizeof(a[0]), &cmp);

		for (i = 0; i < n; i++)
			s += L(i) + R(i);

		printf("Case %d: %d\n", c, s);
	}

	return 0;
}

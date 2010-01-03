#include <stdio.h>
#include <math.h>

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

int main(void)
{
	int i, s, c;

	for (c = 1; scanf("%d", &n) == 1 && n > 0; c++) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		for (s = 0, i = 1; i < n; i++)
			s += R(i - 1);

		for (i = 1; i < n; i++)
			s += L(i);

		printf("Case %d: %d\n", c, s);
	}

	return 0;
}

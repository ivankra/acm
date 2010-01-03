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
	} else if (i > j) {
		for (t = 0; j >= 0; j--)
			if (a[i] > a[j]) t++;
		return t;
	} else {
		t = recur(i + 1, i + 1);
		t += recur(i, i + 1);
		t += recur(i, i - 1);
		return t;
	}
}

int main(void)
{
	int i, c;

	for (c = 1; scanf("%d", &n) == 1 && n > 0; c++) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);
		printf("Case %d: %d\n", c, recur(0, 0));
	}

	return 0;
}

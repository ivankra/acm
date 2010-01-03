/*
ID: mjf28791
PROG: pprime
LANG: C
*/
#include <stdio.h>

int list[1024], count;

void check(int x)
{
	int i;

	if (x < 2) return;

	for (i = 2; (i * i) <= x; i++)
		if ((x % i) == 0) return;

	for (i = 0; i < count; i++)
		if (list[i] == x) return;

	list[count++] = x;
}

void sort()
{
	int i, j, t;

	for (i = 1; i < count; i++) {
		for (t = list[i], j = i - 1; j >= 0 && list[j] > t; j--)
			list[j + 1] = list[j];
		list[j + 1] = t;
	}
}

void make()
{
	int i, x, y, m, t, len;

	count = 0;

	for (x = 0, len = 0, m = 1; x <= 10000; x++) {
		if (x >= m) {
			len++;
			m *= 10;
		}

		for (i = 0, t = x, y = 0; i < len; i++, t /= 10)
			y = y * 10 + (t % 10);

		if (y > 2 && (y & 1) == 0)
			continue;

		check(x * m + y);

		if (len >= 4)
			continue;

		for (i = 0; i < 10; i++)
			check(x * m * 10 + i * m + y);
	}

	sort();
}

int main()
{
	int i, a, b;

	make();

	freopen("pprime.in", "r", stdin);
	freopen("pprime.out", "w", stdout);

	scanf("%d %d", &a, &b);

	for (i = 0; i < count; i++)
		if (a <= list[i] && list[i] <= b)
			printf("%d\n", list[i]);

	return 0;
}

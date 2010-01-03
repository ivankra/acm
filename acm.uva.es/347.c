#include <stdio.h>
#include <string.h>

int list[1024], count;
int a[16], u[16], n;

void check()
{
	static int r[16];
	int i, j;

	for (i = 0; i < n; i++)
		r[i] = 0;

	for (i = 0, j = n; j-- > 0; i = (i + a[i]) % n)
		if (r[i]++) return;

	if (i != 0)
		return;

	for (j = 0, i = 0; i < n; i++)
		j = j * 10 + a[i];
	list[count++] = j;
}

void make()
{
	int i;

	for (i = 1; i <= 9; i++) {
		if (u[i])
			continue;

		a[n++] = i;
		check();

		if (n < 9) {
			u[i] = 1;
			make();
			u[i] = 0;
		}

		n--;
	}
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

int main()
{
	int i, t, x;

	memset(u, 0, sizeof(u));
	count = n = 0;

	make();
	sort();

	for (t = 1; scanf("%d", &x) == 1 && x > 0; t++) {
		for (i = 0; list[i] < x; i++);
		printf("Case %d: %d\n", t, list[i]);
	}

	return 0;
}

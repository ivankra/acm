#include <stdio.h>

#define MAXN (2 * 1048576)
#define MAXP 2048
#define MAXS 1024

int listx[MAXN], listy[MAXN], listn;
char tab[MAXS+MAXS][MAXS+MAXS];

int rel(int x, int y)
{
	if (y < 0)
		y = -y;

	if (x < 0)
		x = -x;

	if (((x | y) & 1) == 0)
		return 0;

	for (;;) {
		if (x == 0) return (y == 1);
		if (y == 0) return (x == 1);

		while ((x & 1) == 0) x >>= 1;
		while ((y & 1) == 0) y >>= 1;

		if (y > x)
			y -= x;
		else
			x -= y;
	}
}

void check(int x, int y)
{
	int i;

	if (y < 0) {
		y = -y;
		x = -x;
	}

	if (tab[x + MAXS][y + MAXS])
		return;

	if (y == 0 || !rel(x, y))
		return;

	listx[listn] = x;
	listy[listn] = y;
	listn++;

	tab[x + MAXS][y + MAXS] = 1;
}

void make()
{
	int i, p, x, y;

	memset(tab, 0, sizeof(tab));

	for (listn = 0, x = 0, y = 0, p = 1; p < (MAXP-8);) {
		for (i = 0; i < p; i++)
			check(++x, y);


		for (i = 0; i < p; i++)
			check(x, ++y);

		p++;

		for (i = 0; i < p; i++)
			check(--x, y);

		for (i = 0; i < p; i++)
			check(x, --y);

		p++;
	}
}

int main()
{
	int n;

	make();

	while (scanf("%d", &n) == 1)
		printf("%d / %d\n", listx[n], listy[n]);

	return 0;
}

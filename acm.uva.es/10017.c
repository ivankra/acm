#include <stdio.h>

int p[4][1024], pn[4], m;

void show()
{
	int i, k;

	for (k = 0; k < 3; k++) {
		printf("%c=>%s", "ABC"[k], (pn[k] == 0) ? "" : "  ");
		for (i = 0; i < pn[k]; i++)
			printf(" %d", p[k][i]);
		printf("\n");
	}
	printf("\n");
}

void move(int x, int y)
{
	if (m-- >= 1) {
		p[y][pn[y]++] = p[x][--pn[x]];
		show();
	}
}

void solve(int x, int y, int t, int n)
{
	if (m < 1 || n < 1)
		return;

	solve(x, t, y, n - 1);
	move(x, y);
	solve(t, y, x, n - 1);
}

int main()
{
	int i, n, t;

	for (t = 1; scanf("%d %d", &n, &m) == 2 && n > 0; t++) {
		printf("Problem #%d\n\n", t);

		pn[1] = pn[2] = 0;
		for (pn[0] = n, i = 0; i < n; i++)
			p[0][i] = n - i;

		show();

		solve(0, 2, 1, n);
	}

	return 0;
}

#include <stdio.h>

int curx, cury;

void move(int x, int y)
{
	printf("(%d,%d)(%d,%d)\n", curx, cury, x, y);
	curx = x;
	cury = y;
}

void rmove(int dx, int dy)
{
	move(curx + dx, cury + dy);
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

void solve(int p, int q)
{
	int i, w = curx * 2, h = cury;

	move(0, 0);

	for (i = 0; i < p; i++) {
		rmove(w >> (p - max(i - 1, 0)), 0);
		rmove(-(w >> (p - i + 1)), h >> (p - i));
		rmove(w >> (p - i), 0);
		rmove(-(w >> (p - i + 1)), -(h >> (p - i)));
	}

	for (i = 2; i <= q; i++) {
		rmove(w >> i, 0);
		rmove(-(w >> (i + 1)), h >> i);
		rmove(w >> i, 0);
		rmove(-(w >> (i + 1)), -(h >> i));
	}

	move(w, 0);
	move(w / 2, h);
}

int main()
{
	int p, q, t;

	for (scanf("%d", &t); t-- > 0;) {
		scanf("%d %d %d %d", &p, &q, &curx, &cury);
		solve(p, q);
		printf("\n");
	}

	return 0;
}

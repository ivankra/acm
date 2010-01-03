#include <stdio.h>

int cx[131072], cy[131072], x, y, n;

void move(int dx, int dy, int k)
{
	while (k-- > 0) {
		++n;
		cx[n] = x;
		cy[n] = y;
		x += dx;
		y += dy;
	}
}

void make()
{
	int m;

	x = y = n = 0;
	move(0, 1, 1);

	for (m = 1; m < 185; m++) {
		move(-1, 0, m);
		move(0, -1, m);
		move(1, -1, m);
		move(1, 0, m);
		move(0, 1, m);
		move(0, 1, 1);
		move(-1, 1, m);
	}
}

int main()
{
	int a;

	make();
	while (scanf("%d", &a) == 1)
		printf("%d %d\n", cx[a], cy[a]);

	return 0;
}

#include <stdio.h>

char a[16][16];
int x, y, d;
int dx[] = { 1, 0, -1, 0}, dy[] = { 0, -1, 0, 1 };

void draw(int n, int w)
{
/*printf("draw x=%d y=%d d=%d n=%d w=%d\n",x-8,-(y-8),d,n,w);*/
	if (n == 1) {
		if (w) d = (d + 2) & 3;

printf("(%d,%d)->(%d,%d)\n", x-8,-(y-8),x+dx[d]-8,-(y+dy[d]-8));


		if (d == 0)
			a[y][x+1] = '_', x += dx[d];
		else if (d == 1)
			a[y][x] = '|';
		else if (d == 2)
			a[y][x-1] = '_', x += dx[d];
		else
			a[y+1][x] = '|';

/*		if (d == 0)
			a[y][x] = '_';
		else if (d == 1)
			a[y][x] = '|';
		else if (d == 2)
			a[y][x +1 - 1] = '_';
		else
			a[y + 1][x - 1] = '|';
*/
		x += dx[d];
		y += dy[d];

		if (w) d = (d + 2) & 3;
		return;
	}

	if (w == 0) {
		draw(n - 1, w);
		d = (d + 3) & 3;
		draw(n - 1, !w);
	} else {
		draw(n - 1, !w);
		d = (d + 1) & 3;
		draw(n - 1, w);
	}
}

int main()
{
	int i, j, n;

	scanf("%d", &n);

	x = y = 8;
	d = 0;
	memset(a, ' ', sizeof(a));

	draw(n, 0);

	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16 && a[i][j] == ' '; j++);
		if (j == 16) continue;
		printf("%.15s\n", a[i]);
	}

	return 0;
}

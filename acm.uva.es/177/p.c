#include <stdio.h>

#define MAXW 512
#define MAXH 256

int dx[] = { 1, 0, -1, 0}, dy[] = { 0, -1, 0, 1 };
int x, y, d;
char a[MAXH][MAXW];

void draw(int n, int w)
{
	if (n == 0) {
		if (w) d = (d + 2) & 3;

		if (d == 0)
			a[y][x+1] = '_';
		else if (d == 1)
			a[y][x] = '|';
		else if (d == 2)
			a[y][x-1] = '_';
		else
			a[y+1][x] = '|';

		if (d == 0 || d == 2)
			x += dx[d];

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
	int i, j, n, c;

	while (scanf("%d", &n) == 1 && n > 0) {
		x = MAXW / 2;
		y = MAXH / 2;
		d = 0;
		memset(a, ' ', sizeof(a));

		draw(n, 0);

		for (i = 0, c = MAXW; i < MAXH; i++) {
			for (j = 0; j < MAXW && a[i][j] == ' '; j++);

			if (j >= MAXW) {
				a[i][0] = '\0';
				continue;
			}

			if (j < c) c = j;
			for (j = MAXW - 1; a[i][j - 1] == ' '; j--);
			a[i][j] = '\0';
		}

		for (i = 0; i < MAXH; i++)
			if (a[i][0] != '\0') printf("%s\n", a[i] + c);
		printf("^\n");
	}

	return 0;
}

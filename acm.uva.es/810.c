#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int dice[24], dice_top[24], dice_front[24];
int roll_right[24], roll_left[24], roll_up[24], roll_down[24];

void xrot(int a[])
{
	int t = a[0];
	a[0] = a[1];
	a[1] = a[3];
	a[3] = a[5];
	a[5] = t;
}

void yrot(int a[])
{
	int t = a[0];
	a[0] = a[4];
	a[4] = a[3];
	a[3] = a[2];
	a[2] = t;
}

void zrot(int a[])
{
	int t = a[1];
	a[1] = a[2];
	a[2] = a[5];
	a[5] = a[4];
	a[4] = t;
}

int get(int a[])
{
	int i, t;

	for (t = 0, i = 0; i < 6; i++)
		t = t * 6 + a[i] - 1;

	for (i = 0; i < 24; i++)
		if (dice[i] == t) break;

	return i;
}

void make_dices()
{
	static int a[6] = { 3, 6, 5, 4, 2, 1 };
	int i, k, t, x, y, z;

	for (k = 0, x = 0; x < 4; x++, xrot(a)) {
		for (y = 0; y < 4; y++, yrot(a)) {
			for (z = 0; z < 4; z++, zrot(a)) {
				for (t = 0, i = 0; i < 6; i++)
					t = t * 6 + a[i] - 1;

				for (i = 0; i < k; i++)
					if (dice[i] == t) break;

				if (i == k) {
					dice[k] = t;
					dice_top[k] = a[0];
					dice_front[k] = a[1];
					k++;
				}
			}
		}
	}

	for (k = 0; k < 24; k++) {
		for (i = 5, t = dice[k]; i >= 0; i--, t /= 6)
			a[i] = (t % 6) + 1;

		yrot(a);
		roll_right[k] = get(a);
		yrot(a);
		yrot(a);
		roll_left[k] = get(a);
		yrot(a);

		xrot(a);
		roll_up[k] = get(a);
		xrot(a);
		xrot(a);
		roll_down[k] = get(a);
	}
}

int dist[2400], pred[2400], queue[8192], head, tail, start;
int map[16][16], nrows, ncols, st_r, st_c, st_d;

int encode(int r, int c, int d)
{
	return ((r * ncols + c) * 24 + d);
}

void decode(int s, int *r, int *c, int *d)
{
	(*d) = s % 24;
	s /= 24;
	(*r) = s / ncols;
	(*c) = s % ncols;
}

void check(int r, int c, int d, int p, int t)
{
	int s;

	if (0 <= r && r < nrows && 0 <= c && c < ncols &&
            map[r][c] != 0 && (map[r][c] < 0 || map[r][c] == t) &&
	    dist[s = encode(r, c, d)] == 0) {
		dist[s] = dist[p] + 1;
		pred[s] = p;
		queue[tail++] = s;
	}
}

void solve()
{
	static int path_r[4096], path_c[4096];
	int i, k, x, r, c, d;

	memset(dist, 0, sizeof(dist));
	head = tail = 0;
	queue[tail++] = encode(st_r, st_c, st_d);

	for (; head < tail; head++) {
		decode(x = queue[head], &r, &c, &d);
		if (r == st_r && c == st_c && dist[x] != 0) break;
		check(r - 1, c, roll_up[d], x, dice_top[d]);
		check(r + 1, c, roll_down[d], x, dice_top[d]);
		check(r, c - 1, roll_left[d], x, dice_top[d]);
		check(r, c + 1, roll_right[d], x, dice_top[d]);
	}

	if (head >= tail) {
		printf("  No Solution Possible\n");
		return;
	}

	for (k = 0;; x = pred[x]) {
		decode(x, &r, &c, &d);
		path_r[k] = r + 1;
		path_c[k] = c + 1;
		if (k++ != 0 && r == st_r && c == st_c) break;
	}

	for (i = 0; k-- > 0; i++) {
		if ((i % 9) == 0) printf(i ? "\n  " : "  ");
		printf((k ? "(%d,%d)," : "(%d,%d)"), path_r[k], path_c[k]);
	}
	printf("\n");
}

int main()
{
	static char name[256];
	int i, j, st, sf;

	make_dices();

	while (scanf(" %s", name) == 1 && strcmp(name, "END") != 0) {
		scanf("%d%d%d%d%d%d", &nrows, &ncols, &st_r, &st_c, &st, &sf);
		st_r--;
		st_c--;

		for (i = 0; i < nrows; i++)
			for (j = 0; j < ncols; j++)
				scanf("%d", &map[i][j]);

		for (st_d = 0; st_d < 24; st_d++)
			if (dice_top[st_d] == st && dice_front[st_d] == sf) break;
		if (st_d == 24) { for(;;)malloc(10000000); }

		printf("%s\n", name);
		solve();
	}

	return 0;
}

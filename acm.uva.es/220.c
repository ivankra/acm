#include <stdio.h>
#include <assert.h>

int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 }, dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int a[8][8];

int valid(int r, int c)
{
	return (0 <= r && r < 8 && 0 <= c && c < 8);
}

int possible(int r, int c, int p)
{
	int d, t, o = (p == 'B') ? 'W' : 'B';

	if (a[r][c] != '-') return 0;

	for (d = 0; d < 8; d++) {
		for (t = 1; valid(r + t * dr[d], c + t * dc[d]); t++)
			if (a[r + t * dr[d]][c + t * dc[d]] != o) break;
		if (t < 2 || !valid(r + t * dr[d], c + t * dc[d])) continue;
		if (a[r + t * dr[d]][c + t * dc[d]] != p) continue;

		return 1;
	}

	return 0;
}

void move(int r, int c, int p)
{
	int d, t, o = (p == 'B') ? 'W' : 'B';

	assert(possible(r, c, p));

	a[r][c] = p;
	for (d = 0; d < 8; d++) {
		for (t = 1; valid(r + t * dr[d], c + t * dc[d]); t++)
			if (a[r + t * dr[d]][c + t * dc[d]] != o) break;
		if (t < 2 || !valid(r + t * dr[d], c + t * dc[d])) continue;
		if (a[r + t * dr[d]][c + t * dc[d]] != p) continue;

		for (t = 1; valid(r + t * dr[d], c + t * dc[d]); t++) {
			if (a[r + t * dr[d]][c + t * dc[d]] != o) break;
			a[r + t * dr[d]][c + t * dc[d]] = p;
		}
	}
}

int main()
{
	char s[1024];
	int i, j, k, m, p, t;

	for (scanf("%d", &t); t-- > 0;) {
		for (i = 0; i < 8; i++)
			for (j = 0; j < 8 && (k = getchar()) != EOF;)
				if (k == '-' || k == 'B' || k == 'W')
					a[i][j++] = k;

		while ((p = getchar()) != EOF && p != 'W' && p != 'B');

		while (gets(s) && s[0] != 'Q') {
			if (s[0] == 'L') {
				for (i = k = 0; i < 8; i++)
					for (j = 0; j < 8; j++)
						if (possible(i, j, p))
							printf(k++ ? " (%d,%d)" : "(%d,%d)", i+1, j+1);
				printf(k ? "\n" : "No legal move.\n");
			} else if (s[0] == 'M') {
				i = s[1] - '1';
				j = s[2] - '1';

				if (!possible(i, j, p))
					p = (p == 'W') ? 'B' : 'W';

				move(i, j, p);

				for (i = k = m = 0; i < 8; i++)
					for (j = 0; j < 8; j++)
						if (a[i][j] == 'B')
							k++;
						else if (a[i][j] == 'W')
							m++;
				printf("Black - %2d White - %2d\n", k, m);

				p = (p == 'W') ? 'B' : 'W';
			}
		}

		for (i = 0; i < 8; i++)
			for (j = 0; j < 8; j++)
				printf((j == 7) ? "%c\n" : "%c", a[i][j]);
	
		if (t) printf("\n");
	}

	return 0;
}

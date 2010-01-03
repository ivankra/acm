#include <stdio.h>
#include <string.h>

#define INF 0x1FFFFFFF

int dx[] = { -1, 0, 1, 0 }, dy[] = { 0, -1, 0, 1 };
int tab[16][32][32], map[32][32], done[16][32][32], width, height;
int wtab[16][32][32], dtab[16][32][32];

void make(int z)
{
	int i, j, t, d, w;

	for (i = 1; i <= height; i++) {
		for (j = 1; j <= width; j++) {
			tab[z][i][j] = INF;
			wtab[z][i][j] = z;

			if ('A' <= map[i][j] && map[i][j] <= 'D' &&
			    ((z >> (map[i][j] - 'A')) & 1)) {
				tab[z][i][j] = tab[z ^ (1 << (map[i][j] - 'A'))][i][j];
				continue;
			}

			for (w = 1; w < z; w++) {
				if ((z & w) != w) continue;

				for (d = 0; d < 4; d++) {
					if (map[i + dy[d]][j + dx[d]] == '#')
						continue;

					t = tab[z ^ w][i + dy[d]][j + dx[d]] +
					    tab[w][i][j];

					if (t < tab[z][i][j]) {
						tab[z][i][j] = t;
						wtab[z][i][j] = w;
						dtab[z][i][j] = d;
					}
				}
			}
		}
	}

	do {
		for (w = 0, i = 1; i <= height; i++) {
			for (j = 1; j <= width; j++) {
				for (d = 0; d < 4; d++) {
					if (map[i + dy[d]][j + dx[d]] == '#')
						continue;

					t = tab[z][i + dy[d]][j + dx[d]] +
					    tab[0][i][j];

					if (t < tab[z][i][j]) {
						tab[z][i][j] = t;
						wtab[z][i][j] = 0;
						dtab[z][i][j] = d;
						w++;
					}
				}
			}
		}
	} while (w);
}

void apply(int z, int y, int x)
{
	int d, w;

	if ('A' <= map[y][x] && map[y][x] <= 'D' &&
	    ((z >> (map[y][x] - 'A')) & 1))
		z ^= (1 << (map[y][x] - 'A'));

	if (map[y][x] == 'o')
		map[y][x] = '.';

	if (z == 0 || done[z][y][x]) return;
	done[z][y][x] = 1;

	d = dtab[z][y][x];
	w = wtab[z][y][x];

	apply(z ^ w, y + dy[d], x + dx[d]);
	apply(w, y, x);
}

int main()
{
	static int s[] = {
		1, 2, 4, 8, 1+2, 1+4, 1+8, 2+4, 2+8, 4+8, 1+2+4, 1+2+8, 1+4+8,
		2+4+8, 1+2+4+8, -1
	};
	int i, j, k;

	while (scanf("%d %d", &width, &height) == 2 && width > 0) {
		for (i = 0; i < 32; i++)
			for (j = 0; j < 32; j++)
				map[i][j] = '#';

		for (i = 1; i <= height; i++)
			for (j = 1; j <= width && (k = getchar()) != EOF;)
				if (strchr("#.oABCD", k) != NULL)
					map[i][j++] = k;

		for (i = 0; i <= (height + 1); i++) {
			for (j = 0; j <= (width + 1); j++) {
				if (map[i][j] == '#')
					tab[0][i][j] = INF;
				else if (map[i][j] == 'o')
					tab[0][i][j] = 1;
				else
					tab[0][i][j] = 0;
			}
		}

		for (i = 0; s[i] >= 0; i++)
			make(s[i]);

		for (i = j = 1; i <= height; i++) {
			for (j = 1; j <= width; j++)
				if ('A' <= map[i][j] && map[i][j] <= 'D') break;
			if (j <= width) break;
		}

		memset(done, 0, sizeof(done));
		apply(15, i, j);

		printf("%d %d\n", width, height);
		for (i = 1; i <= height; i++) {
			for (j = 1; j <= width; j++)
				putchar(map[i][j]);
			putchar('\n');
		}
		putchar('\n');
	}

	printf("0 0\n");
	return 0;
}

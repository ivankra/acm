#include <stdio.h>
#include <ctype.h>

static char map[1024][1024];
static int w, h;

static void search(int y, int x)
{
	static int st[1048576];
	int c, *s;

	c = map[y][x];
	map[y][x] = 0;

	s = st;
	*s++ = y;
	*s++ = x;

	while (s > st) {
		x = *--s;
		y = *--s;

#define CHECK(Y,X) if (map[Y][X] == c) { *s++ = (Y); *s++ = (X); map[Y][X] = 0; }

		CHECK(y + 1, x);
		CHECK(y - 1, x);
		CHECK(y, x + 1);
		CHECK(y, x - 1);
	}
}

int main()
{
	static int cnt[32], rank[32], n, t;
	int i, j, c;

	for (scanf("%d", &n), t = 1; t <= n && scanf("%d %d", &h, &w) == 2; t++) {
		for (i = 1; i <= h; i++)
			for (j = 1; j <= w && (c = getchar()) != EOF;)
				if (isalpha(c)) map[i][j++] = c;

		for (i = 0; i <= w; i++)
			map[0][i] = map[h+1][i] = 0;

		for (i = 0; i <= h; i++)
			map[i][0] = map[i][w+1] = 0;

		for (i = 0; i < 26; i++)
			cnt[i] = 0;

		for (i = 1; i <= h; i++) {
			for (j = 1; j <= w; j++) {
				if (map[i][j] != 0) {
					cnt[map[i][j] - 'a']++;
					search(i, j);
				}
			}
		}

		printf("World #%d\n", t);

		for (rank[0] = 0, i = 1; i < 26; i++) {
			for (j = i - 1; j >= 0 && cnt[rank[j]] < cnt[i]; j--)
				rank[j + 1] = rank[j];
			rank[j + 1] = i;
		}

		for (i = 0; i < 26; i++)
			if (cnt[rank[i]] != 0)
				printf("%c: %d\n", rank[i] + 'a', cnt[rank[i]]);
	}

	return 0;
}

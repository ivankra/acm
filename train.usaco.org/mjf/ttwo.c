/*
ID: mjf28791
PROG: ttwo
LANG: C
*/
#include <stdio.h>
#include <string.h>

typedef struct {
	int x1, y1, d1, x2, y2, d2;
} state_t;

int wall[16][16], dy[] = { -1, 0, 1, 0 }, dx[] = { 0, 1, 0, -1 };
unsigned flag[8192];

int mark(int s)
{
	if ((flag[s >> 5] >> (s & 31)) & 1)
		return 1;

	flag[s >> 5] |= 1U << (s & 31);
	return 0;
}

int encode(state_t s)
{
	int r;
	r = ((s.y1 - 1) * 10 + (s.x1 - 1)) * 4 + s.d1;
	r = ((r * 10 + (s.y2 - 1)) * 10 + (s.x2 - 1)) * 4 + s.d2;
	return r;
}

int main()
{
	int i, j, k;
	state_t s;

	freopen("ttwo.in", "r", stdin);
	freopen("ttwo.out", "w", stdout);

	memset(flag, 0, sizeof(flag));

	memset(wall, 1, sizeof(wall));
	for (i = 1; i <= 10; i++)
		for (j = 1; j <= 10 && (k = getchar()) != EOF;)
			if (k == '.')
				wall[i][j++] = 0;
			else if (k == '*')
				wall[i][j++] = 1;
			else if (k == 'C')
				wall[s.y1 = i][s.x1 = j++] = 0;
			else if (k == 'F')
				wall[s.y2 = i][s.x2 = j++] = 0;
	s.d1 = s.d2 = 0;

	for (k = 0; s.x1 != s.x2 || s.y1 != s.y2; k++) {
#if 0
		printf("%3d: (%d,%d:%c) (%d,%d:%c) => %d\n",
			k, s.y1, s.x1, "NESW"[s.d1], s.y2, s.x2, "NESW"[s.d2],
			encode(s));
#endif

		if (mark(encode(s))) {
			k = 0;
			break;
		}

		if (wall[s.y1 + dy[s.d1]][s.x1 + dx[s.d1]])
			s.d1 = (s.d1 + 1) & 3;
		else
			s.x1 += dx[s.d1], s.y1 += dy[s.d1];

		if (wall[s.y2 + dy[s.d2]][s.x2 + dx[s.d2]])
			s.d2 = (s.d2 + 1) & 3;
		else
			s.x2 += dx[s.d2], s.y2 += dy[s.d2];
	}

	printf("%d\n", k);
	return 0;
}

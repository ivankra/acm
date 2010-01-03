#include <stdio.h>
#include <string.h>

void solve(int h)
{
	static int left[1024], right[1024], nleft, nright;
	static char s[512][128];
	int i, j, k, x, y;

	for (nleft = 0, k = 1, i = h; k <= i; i -= k++)
		left[nleft++] = k;
	left[nleft - 1] += i;

	for (nright = nleft - 1, i = 0; i < nright; i++)
		right[i] = left[i];
	right[nright - 1] += left[nleft - 1];

	memset(s, ' ', sizeof(s));

	for (i = nleft - 1, x = 0, y = h - 1; i >= 0; i--) {
		for (j = left[i] - 1; j > 0; j--)
			s[y--][x] = '#';

		s[y][x + 1] = '*';
		s[y][x + 2] = '*';
		s[y--][x] = '#';
		x += 2;
	}

	for (i = nright - 1, x = (nleft + nright) * 2 + 1, y = h - 1; i >= 0; i--) {
		for (j = right[i] - 1; j > 0; j--)
			s[y--][x] = '#';

		s[y][x - 1] = '*';
		s[y][x - 2] = '*';
		s[y--][x] = '#';
		x -= 2;
	}

	for (i = 0; i < h; i++) {
		for (j = 0; s[i][j] != '#'; j++);

		for (j++; s[i][j] != '#'; j++)
			if (s[i][j] == ' ') s[i][j] = '.';

		s[i][j + 1] = '\0';

		printf("%s\n", s[i]);
	}

	printf("\n");
}

int main()
{
	int h, t;

	for (t = 1; scanf("%d", &h) == 1; t++) {
		printf("Tower #%d\n", t);
		solve(h);
	}

	return 0;
}

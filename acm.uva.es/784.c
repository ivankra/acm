#include <stdio.h>
#include <string.h>

int write(int, char *, int);

int main()
{
	static char data[64][128];
	static int st[16384], stp, t, h;
	int i, j, y, x, r;
	char *p;

	for (scanf("%d\n", &t); t-- > 0;) {
		memset(data, '\0', sizeof(data));
		for (h = 0; h < 64;) {
			if (fgets(data[h], 126, stdin) == NULL) break;
			if (data[h++][0] == '_') break;
		}

		for (stp = 0, i = 0; i < h; i++) {
			for (j = 0; data[i][j]; j++) {
				if (data[i][j] == '*') {
					st[stp++] = i;
					st[stp++] = j;
				}
			}
		}

		while (stp >= 2) {
			x = st[--stp];
			y = st[--stp];

			if (data[y][x] == '#')
				continue;

			data[y][x] = '#';

			for (r = x; x > 0 && data[y][x - 1] == ' ';)
				data[y][--x] = '#';

			while (data[y][r + 1] == ' ')
				data[y][++r] = '#';

			if (y > 0) {
				for (i = 0, j = 0; x <= r; x++) {
					if (data[y - 1][x] != ' ') {
						i = 0;
					} else if (i++ == 0) {
						st[stp++] = y - 1;
						st[stp++] = x;
					}

					if (data[y + 1][x] != ' ') {
						j = 0;
					} else if (j++ == 0) {
						st[stp++] = y + 1;
						st[stp++] = x;
					}
				}
			} else {
				for (i = 0, y++; x <= r; x++) {
					if (data[y][x] != ' ') {
						i = 0;
					} else if (i++ == 0) {
						st[stp++] = y;
						st[stp++] = x;
					}
				}
			}
		}

		for (i = 0, p = (char *)data; i < h; i++)
			for (j = 0; data[i][j] != '\0'; j++)
				*p++ = data[i][j];

		write(1, (char *)data, p - (char *)data);
	}

	return 0;
}

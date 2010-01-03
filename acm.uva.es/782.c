#include <stdio.h>
#include <string.h>

int write(int, char *, int);

int main()
{
	static char data[64][128], sep[256], output[16384];
	static int st[16384], stp, t, h;
	int i, j, y, x, r;
	char *p;

	for (scanf("%d%*1[\n]", &t); t-- > 0;) {
		memset(data, ' ', sizeof(data));
		for (h = 0; h < 64; h++) {
			if (fgets(data[h], 128, stdin) == NULL) break;

			if (data[h][0] == '_') {
				strcpy(sep, data[h]);
				memset(data[h], ' ', 128);
				break;
			}

			for (i = 0; data[h][i] != '\n' && data[h][i]; i++);

			while (i < 128)
				data[h][i++] = ' ';
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

			if (y > (h + 2))
				continue;

			if (data[y][x] == '#')
				continue;

			data[y][x] = '#';

			for (r = x; x > 0 && data[y][x - 1] == ' ';)
				data[y][--x] = '#';

			while (r < 127 && data[y][r + 1] == ' ')
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

		for (i = 0, p = output; i < h; i++) {
			for (j = 0; j < 126; j++, p++) {
				*p = data[i][j];

				if (data[i][j] != '#') continue;

				if (data[i][j + 1] != '#') continue;
				if (data[i + 1][j] != '#') continue;
				if (j > 0 && data[i][j - 1] != '#') continue;
				if (i > 0 && data[i - 1][j] != '#') continue;

				*p = ' ';
			}

			while (p > output && p[-1] == ' ')
				p--;

			*p++ = '\n';
		}

		for (i = 0; sep[i];)
			*p++ = sep[i++];

		write(1, output, p - output);
	}

	return 0;
}

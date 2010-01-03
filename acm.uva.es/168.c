#include <stdio.h>
#include <string.h>
#include <ctype.h>

int cave_exit[32][256], cave_n[32], lit[32], k, x, y;

void solve()
{
	int r, i, c;

	memset(lit, 0, sizeof(lit));

	for (r = 0;;) {
		for (i = c = 0; i < cave_n[x]; i++) {
			c = cave_exit[x][i];

			if (c != x && c != y && lit[c] == 0)
				break;
		}

		if (i >= cave_n[x]) {
			printf("/%c\n", x + 'A');
			return;
		}

		y = x;
		x = c;

		if (++r >= k) {
			printf("%c ", y + 'A');
			lit[y] = 1;
			r = 0;
		}
	}
}

void go(char *s)
{
	int i;

	memset(cave_n, 0, sizeof(cave_n));

	for (;;) {
		while (*s && *s != '.' && !isalpha(*s))
			s++;

		if (*s == '\0' || *s == '.')
			break;

		for (i = toupper(*s++) - 'A'; *s && *s != ';' && *s != '.'; s++)
			if (isalpha(*s))
				cave_exit[i][cave_n[i]++] = toupper(*s) - 'A';
	}

	if (*s == '.')
		s++;

	while (*s && !isalpha(*s)) s++;
	if (*s == '\0') return;
	x = toupper(*s++) - 'A';

	while (*s && !isalpha(*s)) s++;
	if (*s == '\0') return;
	y = toupper(*s++) - 'A';

	sscanf(s, "%d", &k);

	solve();
}

int main()
{
	static char buf[8192];

	while (gets(buf) && buf[0] != '#')
		go(buf);

	return 0;
}

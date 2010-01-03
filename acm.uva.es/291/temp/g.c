#include <stdio.h>

static int check(char *path)
{
	static const char *edges[] = {
		"12", "13", "15", "23", "25", "34", "35", "45"
	};
	static int v[8];
	register int i, j, c;

	for (i = 0; path[i]; i++)
		if (path[i] <= '0' || path[i] > '5') return 0;
	if (i != 9) return 0;

	for (i = 0; i < 8; i++)
		v[i] = 0;

	for (i = 1; i < 9; i++) {
		for (j = 0, c = path[i - 1]; j < 8; j++)
			if ((c == edges[j][0] && path[i] == edges[j][1]) ||
			    (c == edges[j][1] && path[i] == edges[j][0]))
				break;
		if (j >= 8) return 0;

		if (v[j]++ != 0) return 0;
	}

	return 1;
}

int main()
{
	static int k;
	static char buf[1000];

	for (k = 121111111; k < 160000000; k++) {
		sprintf(buf, "%d", k);
		if (check(buf)) {
			printf("%s\n", buf);
			fflush(stdout);
		}

if ((k & 0xFFFFF) == 0) { fprintf(stderr, "[%d]\n", k); }
	}
}

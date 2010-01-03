#include <stdio.h>

int a[4][4];

int playx(void);

int check()
{
	int i;

	for (i = 0; i < 4; i++)
		if (a[i][0] != '.' && a[i][0] == a[i][1] &&
		    a[i][0] == a[i][2] && a[i][0] == a[i][3])
			return a[i][0];

	for (i = 0; i < 4; i++)
		if (a[0][i] != '.' && a[0][i] == a[1][i] &&
		    a[0][i] == a[2][i] && a[0][i] == a[3][i])
			return a[0][i];

	if (a[0][0] != '.' && a[0][0] == a[1][1] && a[0][0] == a[2][2] &&
	    a[2][2] == a[3][3])
		return a[0][0];

	if (a[0][3] != '.' && a[0][3] == a[1][2] && a[0][3] == a[2][1] &&
	    a[0][3] == a[3][0])
		return a[0][3];

	return 0;
}

int playo()
{
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (a[i][j] != '.')
				continue;

			a[i][j] = 'o';
			if (check() == 'o' || playx() < 0) {
				a[i][j] = '.';
				return 1;
			}

			a[i][j] = '.';
		}
	}

	return 0;
}

int playx()
{
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (a[i][j] != '.')
				continue;

			a[i][j] = 'x';
			if (check() == 'x' || playo() == 0) {
				a[i][j] = '.';
				return ((i << 8) | j);
			}

			a[i][j] = '.';
		}
	}

	return -1;
}

int main()
{
	int i, j, c;

	while ((c = getchar()) != EOF && c != '$') {
		if (c != '?')
			continue;

		for (i = 0; i < 4; i++)
			for (j = 0; (c = getchar()) != EOF && j < 4;)
				if (c == '.' || c == 'x' || c == 'o')
					a[i][j++] = c;

		i = playx();

		if (i < 0)
			printf("#####\n");
		else
			printf("(%d,%d)\n", (i >> 8), i & 0xFF);
	}

	return 0;
}

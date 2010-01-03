#include <stdio.h>
#include <string.h>

int c[32][32], d[32], p[32], n, T;

int solve()
{
	int x, y;

	for (int k = 0; k < 26; k++)
		for (int i = 0; i < 26; i++)
			for (int j = 0; j < 26; j++)
				c[i][j] |= c[i][k] & c[k][j];

	for (int i = 0; i < 26; i++)
		for (int j = i+1; j < 26; j++)
			if (p[i] && p[j] && !c[i][j])
				return 0;

	x = y = -1;
	for (int i = 0; i < 26; i++) {
		if (d[i] == -1) {
			if (x != -1) return 0;
			x = i;
		} else if (d[i] == 1) {
			if (y != -1) return 0;
			y = i;
		} else if (d[i] != 0) {
			return 0;
		}
	}

	return (x == -1 && y == -1) || (x != -1 && y != -1);
}

int main()
{
	char s[1024];

	for (scanf("%d", &T); T-- > 0 && scanf("%d", &n) == 1;) {
		memset(c, 0, sizeof(c));
		memset(d, 0, sizeof(d));
		memset(p, 0, sizeof(p));

		while (n-- && scanf(" %s", s) == 1) {
			int x = s[0] - 'a', y = s[strlen(s)-1] - 'a';
			c[x][y] = c[y][x] = p[x] = p[y] = 1;
			d[x]++; d[y]--;
		}

		if (solve())
			printf("Ordering is possible.\n");
		else
			printf("The door cannot be opened.\n");	
	}

	return 0;
}

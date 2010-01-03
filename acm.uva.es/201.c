#include <stdio.h>
#include <string.h>

int hl[16][16], vl[16][16], n;

int vline(int r, int c, int k)
{
	int i;

	for (i = 0; i < k; i++, r++)
		if (vl[r][c] == 0) return 0;

	return 1;
}

int hline(int r, int c, int k)
{
	int i;

	for (i = 0; i < k; i++, c++)
		if (hl[r][c] == 0) return 0;

	return 1;
}

int count(int k)
{
	int i, j, c;

	for (c = 0, i = 1; i <= (n - k); i++) {
		for (j = 1; j <= (n - k); j++) {
			if (vline(i, j, k) && hline(i, j, k) &&
			    hline(i + k, j, k) && vline(i, j + k, k)) {
				c++;
			}
		}
	}

	return c;
}

int main()
{
	char s[128];
	int i, m, p, r, c;

	for (p = 1; scanf("%d %d", &n, &m) == 2 && n > 0; p++) {
		if (p > 1)
			printf("\n**********************************\n\n");
		printf("Problem #%d\n\n", p);

		memset(hl, 0, sizeof(hl));
		memset(vl, 0, sizeof(vl));

		while (m-- > 0 && scanf(" %s %d %d", s, &r, &c) == 3) {
			if (s[0] == 'H')
				hl[r][c] = 1;
			else
				vl[c][r] = 1;
		}

		for (m = 0, i = 1; i <= n; i++) {
			if ((r = count(i)) != 0) {
				printf("%d square (s) of size %d\n", r, i);
				m++;
			}
		}

		if (m == 0)
			printf("No completed squares can be found.\n");
	}

	return 0;
}

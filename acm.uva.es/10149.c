#include <stdio.h>
#include <string.h>

int score[16][16];
int tab[65536], choice[65536];

int search(int k, int mask)
{
	int i, j;

	if (tab[mask] >= 0)
		return tab[mask];

	if (k <= 0)
		return (tab[mask] = 0);

	for (i = 0; i < 13; i++) {
		if (((mask >> i) & 1) == 1)
			continue;

		j = score[i+1][k] + search(k - 1, mask | (1 << i));
		if (j > tab[mask]) {
			tab[mask] = j;
			choice[mask] = i;
		}
	}

	if (k == 6 && tab[mask] >= 63)
		tab[mask] += 35;

	return tab[mask];
}

void solve()
{
	static int r[16];
	int i, m, s;

	for (i = 0; i < 16384; i++)
		tab[i] = -1;

	s = search(13, 0);

	for (m = 0, i = 13; i >= 1; i--, m |= 1 << choice[m])
		r[i] = score[choice[m] + 1][i];

	for (i = 1; i <= 13; i++)
		printf("%d ", r[i]);

	for (m = 0, i = 1; i <= 6; i++)
		m += r[i];

	printf("%d %d\n", (m >= 63) ? 35 : 0, s);
}

int take()
{
	static int c[8], p[8];
	int i, j, k, r, d;

	memset(score, 0, sizeof(score));

	for (r = 1; r <= 13; r++) {
		memset(p, 0, sizeof(p));

		for (i = 1; i <= 5; i++) {
			if (scanf("%d", &c[i]) != 1) return 0;
			p[c[i]] = 1;
		}

		for (i = 1; i <= 5; i++) {
			for (k = c[i], j = i - 1; j >= 0 && c[j] > k; j--)
				c[j + 1] = c[j];
			c[j + 1] = k;
		}

		for (i = 1; i <= 5; i++) {
			score[r][c[i]] += c[i];
			score[r][7] += c[i];
		}

		for (i = 2, j = k = d = 1; i <= 5; i++) {
			if (c[i] == c[i - 1]) {
				j++;
			} else {
				j = 1;
				d++;
			}

			if (j > k)
				k = j;
		}

		score[r][8] = (k >= 3) ? score[r][7] : 0;
		score[r][9] = (k >= 4) ? score[r][7] : 0;
		score[r][10] = (k == 5) ? 50 : 0;

		i = (p[1] && p[2] && p[3] && p[4]);
		i = i || (p[2] && p[3] && p[4] && p[5]);
		i = i || (p[3] && p[4] && p[5] && p[6]);
		score[r][11] = i ? 25 : 0;

		i = (p[1] && p[2] && p[3] && p[4] && p[5]);
		i = i || (p[2] && p[3] && p[4] && p[5] && p[6]);
		score[r][12] = i ? 35 : 0;

		score[r][13] = (k == 3 && d == 2) ? 40 : 0;
	}

	return 1;
}

int main()
{
	while (take())
		solve();

	return 0;
}

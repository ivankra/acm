#include <stdio.h>

int prime[4096], pi;
int s[32768], sa[1024], sb[1024], sd[1024], m;

void make()
{
	int i, j, k;

	for (i = 0; i < 32768; i++) s[i] = 0;

	for (pi = 0, i = 2; i < 32768; i++) {
		if (s[i]) continue;
		for (prime[pi++] = i, j = i * i; j < 32768; j += i) s[j] = 1;
	}

	for (i = m = 0; (i + 1) < pi; i += j - 1) {
		k = prime[i + 1] - prime[i];
		for (j = 1; (i + j) < pi; j++)
			if ((prime[i + j] - prime[i + j - 1]) != k) break;

		if (j >= 3) {
			sa[m] = prime[i];
			sb[m] = prime[i + j - 1];
			sd[m] = k;
			m++;
		}
	}
}

int main()
{
	int i, j, k, x, y;

	for (make(); scanf("%d %d", &x, &y) == 2 && (x != 0 || y != 0);) {
		if (x > y) i = x, x = y, y = i;

		for (i = 0; i < m; i++)
			if (x <= sa[i] && sb[i] <= y) {
				for (j = 0, k = sa[i]; k <= sb[i]; k += sd[i])
					printf(j++ ? " %d" : "%d", k);
				putchar('\n');
			}
	}

	return 0;
}

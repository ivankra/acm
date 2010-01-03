#include <stdio.h>

int sim(int n, int m)
{
	static char map[128];
	register int i, j, k, last;

	for (i = 0; i < n; i++) map[i] = 0;
	for (k = 0, last = 0;;) {
		map[k] = 1;
		last = k;
		for (i = 0; i < m; i++) {
			for (j = 0; j < (n+5); j++) {
				k = (k + 1) % n;
				if (map[k] == 0) break;
			}
			if (map[k]) return last;
		}
	}
}

int solve(int n)
{
	int m;
	for (m = 1; ; m++)
		if (sim(n, m) == 12) return m;
	return 0;
}

int main(void)
{
	int i;
	for (i = 0; i <= 100; i++) {
		if (i < 13) printf("0,");
		else printf("%d,", solve(i));
	}
}

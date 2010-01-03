#include <stdio.h>
#include <string.h>

int cast[8192][128], n, m;
char names[128][256];

void solve()
{
	static int elim[1024], votes[1024];
	int i, j, t;

	memset(elim, 0, sizeof(elim));
	elim[0] = 1;

	for (;;) {
		memset(votes, 0, sizeof(votes));
		for (i = 0; i < m; i++) {
			for (j = 1; j <= n && elim[cast[i][j]]; j++);
			if (j > n) continue;
			votes[cast[i][j]]++;
		}

		for (i = 1; i <= n; i++) {
			if (!elim[i] && (2 * votes[i]) > m) {
				printf("%s\n", names[i]);
				return;
			}
		}

		for (t = -1, i = 1; i <= n; i++) {
			if (elim[i]) continue;
			if (t < 0 || votes[i] < t) t = votes[i];
		}

		for (i = 1; i <= n; i++)
			if (!elim[i] && votes[i] != t) break;
		if (i > n) {
			for (i = 1; i <= n; i++)
				if (!elim[i]) printf("%s\n", names[i]);
			return;
		}

		for (i = 1; i <= n; i++)
			if (!elim[i] && votes[i] == t) elim[i] = 1;
	}
}

int main()
{
	static char buf[65536];
	int i, t, x, z;
	char *s;

	while (gets(buf) && sscanf(buf, "%d", &t) != 1);

	while (t-- > 0) {
		while (gets(buf) && sscanf(buf, "%d", &n) != 1);

		memset(names, 0, sizeof(names));
		for (i = 1; i <= n; i++)
			gets(names[i]);

		memset(cast, 0, sizeof(cast));
		for (m = 0; gets(buf); m++) {
			for (s = buf, i = 1; i <= n && sscanf(s, "%d %n", &x, &z) > 0;) {
				if (x < 0 || x > n) x = 0;
				cast[m][i++] = x;
				s += z;
			}
			if (i <= n) break;
		}

		solve();

		if (t > 0) printf("\n");
	}

	return 0;
}

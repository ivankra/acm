#include <stdio.h>
#include <ctype.h>

#define INF 0x1FFFFFFF

#define setmin(a, v) { if ((a) > (v)) (a) = (v); }
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

int main()
{
	static int u[32][32], v[32][32], e, c;
	static char x, y, s, t;
	register int i, j, k;

	while (scanf("%d", &e) == 1 && e > 0) {
		for (i = 0; i < 26; i++) {
			for (j = 0; j < 26; j++) u[i][j] = v[i][j] = INF;
			u[i][i] = v[i][i] = 0;
		}

		while (e-- > 0) {
			scanf(" %c %c %c %c %d", &s, &t, &x, &y, &c);

			s = toupper(s);
			t = toupper(t);
			x = toupper(x);
			y = toupper(y);

			if (s == 'Y') {
				setmin(u[x - 'A'][y - 'A'], c);
				if (t == 'B') setmin(u[y - 'A'][x - 'A'], c);
			} else {
				setmin(v[x - 'A'][y - 'A'], c);
				if (t == 'B') setmin(v[y - 'A'][x - 'A'], c);
			}
		}

		for (k = 0; k < 26; k++) {
			for (i = 0; i < 26; i++) {
				if (i == k || u[i][k] == INF) continue;
				for (j = 0; j < 26; j++)
					setmin(u[i][j], u[i][k] + u[k][j]);
			}
		}

		for (k = 0; k < 26; k++) {
			for (i = 0; i < 26; i++) {
				if (i == k || v[i][k] == INF) continue;
				for (j = 0; j < 26; j++)
					setmin(v[i][j], v[i][k] + v[k][j]);
			}
		}

		scanf(" %c %c", &s, &t);

		s = toupper(s) - 'A';
		t = toupper(t) - 'A';

		for (k = INF, i = 0; i < 26; i++) {
			setmin(k, u[s][i] + v[t][i]);
		}

		if (k == INF) {
			printf("You will never meet.\n");
			continue;
		}

		printf("%d", k);
		for (i = 0, j = 0; i < 26; i++)
			if ((u[s][i] + v[t][i]) == k) printf(" %c",  i + 'A');
		printf("\n");
	}

	return 0;
}

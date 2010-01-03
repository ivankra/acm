#include <stdio.h>
#include <string.h>

#define SRC  1
#define SINK 2

int r[256][256], nvert, nnames;
char names[1024][32];

int get(char *s)
{
	int i;

	for (i = 0; i < nnames; i++)
		if (strcmp(names[i], s) == 0) return i;

	strcpy(names[nnames], s);
	return nnames++;
}

int maxflow()
{
	static int p[1024], s[1024], t, f;
	int i, j;

	for (f = 0;; f++) {
		for (i = 1; i <= nvert; i++)
			p[i] = 0;

		for (p[s[0] = SRC] = SRC, t = 1; t > 0 && p[SINK] == 0;)
			for (i = s[--t], j = 1; j <= nvert; j++)
				if (r[i][j] && p[j] == 0) p[s[t++] = j] = i;

		if (p[SINK] == 0)
			return f;

		for (i = SINK; i != SRC; i = p[i]) {
			r[p[i]][i] = 0;
			r[i][p[i]] = 1;
		}
	}
}

int main()
{
	static int plugs[256], dev[256], adap[256][2], nplugs, ndev, nadap, t;
	static int m[512][512], lp[128], ld[128];
	static char s1[1024], s2[1024];
	int i, j, k;

	for (scanf("%d", &t); t-- > 0;) {
		memset(r, 0, sizeof(r));
		memset(m, 0, sizeof(m));
		nnames = 0;

		scanf("%d", &nplugs);
		for (i = 0; i < nplugs && scanf(" %s", s1) == 1; i++)
			plugs[i] = get(s1);

		scanf("%d", &ndev);
		for (i = 0; i < ndev && scanf(" %s %s", s1, s2) == 2; i++)
			dev[i] = get(s2);

		scanf("%d", &nadap);
		for (i = 0; i < nadap && scanf(" %s %s", s1, s2) == 2; i++) {
			adap[i][0] = get(s1);
			adap[i][1] = get(s2);
		}

		for (i = 0; i < nnames; i++)
			m[i][i] = 1;

		for (i = 0; i < nadap; i++)
			m[adap[i][0]][adap[i][1]] = 1;

		for (k = 0; k < nnames; k++) {
			for (i = 0; i < nnames; i++) {
				if (m[i][k] == 0) continue;
				for (j = 0; j < nnames; j++)
					m[i][j] |= m[i][k] & m[k][j];
			}
		}

		nvert = 2;
		for (i = 0; i < nplugs; i++) {
			lp[i] = ++nvert;
			r[lp[i]][SINK] = 1;
		}

		for (i = 0; i < ndev; i++) {
			ld[i] = ++nvert;
			r[SRC][ld[i]] = 1;
			for (j = 0; j < nplugs; j++)
				if (m[dev[i]][plugs[j]]) r[ld[i]][lp[j]] = 1;
		}

		printf(t ? "%d\n\n" : "%d\n", ndev - maxflow());
	}

	return 0;
}

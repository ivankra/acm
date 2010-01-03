// Algorithm: Knuth-Morris-Pratt + DP
#include <cstdio>
#include <cstring>

#define MAXLEV 31

char prod[2][32], pat[32], src[32];
int next[32][2], M;

int memo[MAXLEV+1][2][16];

int f(int lev, int x, int m) {
	if (lev == 0) return next[m][x];

	int &res = memo[lev][x][m];
	if (res != -1) return res;

	res = m;
	for (int i = 0; prod[x][i]; i++)
		res = f(lev-1, prod[x][i]-'a', res);
	return res;
}

int main() {
	while (gets(prod[0]) && gets(prod[1]) && gets(src) && gets(pat)) {
		M = strlen(pat);

		for (int m = 0; m < M; m++)
		for (int c = 0; c < 2; c++) {
			next[m][c] = 0;
			for (int k = m; k >= 0; k--) {
				if (memcmp(pat, pat+m-k, k) == 0 && pat[k] == 'a'+c) {
					next[m][c] = k + 1;
					break;
				}
			}
		}
		next[M][0] = next[M][1] = M;

		memset(memo, 0xff, sizeof(memo));

		int okay = 0;
		for (int lev = 0; !okay && lev <= MAXLEV; lev++) {
			int t = 0;
			for (int i = 0; src[i]; i++)
				t = f(lev, src[i]-'a', t);
			if (t == M) okay = 1;
		}

		printf(okay ? "YES\n" : "NO\n");
	}
}

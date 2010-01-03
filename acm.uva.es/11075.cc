#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;i++)

char pat[20][8][8], patc[20], goal[32][32], tmp[32][32];
int match[20][32][32];
int N, nrows, ncols, go_char, go_left;

int go(int p) {
	if (go_left == 0) return 1;

	while (p < N && patc[p] != go_char) p++;
	if (p >= N) return 0;

	REP(y, nrows) REP(x, ncols) {
		if (!match[p][y][x]) continue;

		REP(a,5) REP(b,5)
			if (pat[p][a][b] != '.' && tmp[y+a][x+b] != pat[p][a][b]) goto skip;

		REP(a,5) REP(b,5)
			if (pat[p][a][b] != '.') { go_left--; tmp[y+a][x+b] = '.'; }

		if (go(p+1)) return 1;

		REP(a,5) REP(b,5)
			if (pat[p][a][b] != '.') { go_left++; tmp[y+a][x+b] = pat[p][a][b]; }

skip:;
	}

	return 0;
}

int main() {
	int cnt1[256], cnt2[256], T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		memset(cnt1, 0, sizeof(cnt1));
		memset(cnt2, 0, sizeof(cnt2));

		scanf("%d", &N);
		REP(p, N) {
			patc[p] = '.';			
			REP(i,5) REP(j,5) {
				scanf(" %c", &pat[p][i][j]);
				if (pat[p][i][j] != '.' && patc[p] == '.') patc[p] = pat[p][i][j];
				cnt1[(int)pat[p][i][j]]++;
			}
		}

		scanf("%d %d", &nrows, &ncols);
		memset(goal, '.', sizeof(goal));
		REP(i, nrows) REP(j, ncols) {
			scanf(" %c", &goal[i][j]);
			cnt2[(int)goal[i][j]]++;
		}

		int ok = 1;
		for (int c = 'a'; c <= 'z'; c++)
			ok &= (cnt1[c] == cnt2[c]);

		if (ok) {
			REP(p,N) {
				if (patc[p] == '.') continue;

				int y0 = 4, x0 = 4;
				REP(a,5) REP(b,5)
					if (pat[p][a][b] != '.') { y0 <?= a; x0 <?= b; }

				char buf[5][5];
				REP(a,5) REP(b,5) {
					buf[a][b] = '.';
					if (a+y0 < 5 && b+x0 < 5)
						buf[a][b] = pat[p][a+y0][b+x0];
				}

				REP(a,5) REP(b,5) pat[p][a][b] = buf[a][b];
			}

			memset(match, 0, sizeof(match));
			REP(p, N) REP(y, nrows) REP(x, ncols) {
				match[p][y][x] = 1;
				REP(a,5) REP(b,5) {
					if (pat[p][a][b] != '.')
						match[p][y][x] &= (pat[p][a][b] == goal[y+a][x+b]);
				}
			}
		}

		for (int c = 'a'; c <= 'z' && ok; c++) {
			if (cnt1[c] == 0) continue;
			memcpy(tmp, goal, sizeof(goal));
			go_char = c;
			go_left = cnt1[c];
			ok &= go(0);
		}

		printf("Case %d: %s\n", cs, ok ? "Yes" : "No");
	}
}

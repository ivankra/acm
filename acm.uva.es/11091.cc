#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
#define REP(i,n) for(int _REP_N=(n),i=0;i<_REP_N;i++)

#define MOD 10007

int cfg_id[8][8][8][8], ncfg;
struct Config { int a,b,c,d,prev[4],atk[6]; } cfg[500];

int res[50][64], mat[50][64], dim;

void power(int e) {
	static int tmp[50][64];

	memset(res, 0, sizeof(res));
	REP(i, dim) res[i][i] = 1;

	if (e <= 0) return;

	int t;
	for (t = 31; (e & (1 << t)) == 0; t--);

	for (; t >= 0; t--) {
		REP(i,dim) REP(j,dim) {
			tmp[i][j] = 0;
			REP(k,dim) tmp[i][j] = (tmp[i][j] + res[i][k] * res[k][j]) % MOD;
		}

		if (e & (1 << t)) {
			REP(i,dim) REP(j,dim) {
				res[i][j] = 0;
				REP(k,dim) res[i][j] = (res[i][j] + tmp[i][k] * mat[k][j]) % MOD;
			}
		} else {
			REP(i,dim) REP(j,dim) res[i][j] = tmp[i][j];
		}
	}
}

int mir(int r) { return r<6 ? 5-r : 6; }

int main() {
	memset(cfg_id, 0xff, sizeof(cfg_id));
	ncfg = 0;

	REP(a,7) REP(b,7) REP(c,7) REP(d,7) {
		if (cfg_id[a][b][c][d] >= 0 || (a < 6 && a == b) || (c < 6 && c == d)) continue;

		if (a < 6 && c < 6 && c == a-2 || c == a+2) continue;
		if (a < 6 && d < 6 && d == a-2 || d == a+2) continue;

		if (b < 6 && c < 6 && c == b-2 || c == b+2) continue;
		if (b < 6 && d < 6 && d == b-2 || d == b+2) continue;

		if ((a < 6) ^ (b < 6)) continue;
		if ((c < 6) ^ (d < 6)) continue;
		if (a < 6 && c == 6) continue;

		int k = ncfg++;
		assert(k < 50);

		REP(i,2) REP(j,2) {
			cfg_id[i==0?a:b][i==0?b:a][j==0?c:d][j==0?d:c] = k;
			cfg_id[mir(i==0?a:b)][mir(i==0?b:a)][mir(j==0?c:d)][mir(j==0?d:c)] = k;
		}

		Config cf = {a,b,c,d,{a,b,c,d},{0,0,0,0,0,0}};

		REP(i,2) REP(j,2) {
			int c0 = i-2, r0 = cf.prev[2*i+j];
			if (r0 == 6) continue;
			for (int dr = -2; dr <= 2; dr++)
			for (int dc = -2; dc <= 2; dc++) {
				if ((abs(dr)==2 && abs(dc)==1) || (abs(dr)==1 && abs(dc)==2)) {
					int c1 = c0 + dc, r1 = r0 + dr;
					if (c1 == 0 && 0 <= r1 && r1 < 6) cf.atk[r1] = 1;
				}
			}
		}

		cfg[k] = cf;
	}

	memset(mat, 0, sizeof(mat));
	dim = ncfg;

	int root = cfg_id[6][6][6][6];

	REP(i, ncfg) {
		REP(e,6) REP(f,6) {
			if (e >= f || cfg[i].atk[e] || cfg[i].atk[f]) continue;
			assert(cfg_id[cfg[i].c][cfg[i].d][e][f] >= 0);
			mat[i][cfg_id[cfg[i].c][cfg[i].d][e][f]]++;
		}
	}

	int T, N;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d", &N) == 1; cs++) {
		power(N);

		int ans = 0;
		REP(k, dim)
			ans = (ans + res[root][k]) % MOD;
		printf("%d\n", ans);
	}
}

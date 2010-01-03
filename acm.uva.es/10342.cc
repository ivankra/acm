#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;
#define FOR(i,a,b) for(int i=(a),__FOR_B=(b);i<=__FOR_B;i++)
#define REP(i,n) FOR(i,0,(int)(n)-1)

#define INF 0x0fffffff
int N, d[128][128], a[128][128];

int main() {
	int M, x, y, z;
	for (int cs = 1; scanf("%d %d", &N, &M) == 2; cs++) {
		REP(i,N) REP(j,N) a[i][j] = d[i][j] = i==j ? 0 : INF;
		REP(i,M) { scanf("%d %d %d", &x, &y, &z); a[x][y] = a[y][x] = z; }

		REP(i,N) REP(j,N) d[i][j] = a[i][j];
		REP(k,N) REP(i,N) REP(j,N) d[i][j] <?= d[i][k] + d[k][j];

		printf("Set #%d\n", cs);
		scanf("%d", &M);
		while (M-- > 0 && scanf("%d %d", &x, &y) == 2) {
			if (x < 0 || x >= N || y < 0 || y >= N) {
				printf("?\n");
				continue;
			}
			int best = INF;
#define _(expr) if ((expr)>d[x][y]) best<?=(expr)
			REP(i,N) REP(j,N) _(d[x][i] + a[i][j] + d[j][y]);
			printf(best < INF ? "%d\n" : "?\n", best);
		}
	}
}

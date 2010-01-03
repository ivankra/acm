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

int N, flow[64][64], res[64][64];

bool aug(int s, int t) {
	int seen[100], prev[100], qdata[100], *qh=qdata, *qt=qdata;
	memset(seen, 0, sizeof(seen));

	*qt++ = s;
	seen[s] = 1;

	for (; qh < qt && !seen[t];) {
		int x = *qh++;
		for (int y = 0; y < N; y++) {
			if (res[x][y] > 0 && !seen[y]) {
				seen[y] = 1;
				prev[y] = x;
				*qt++ = y;
			}
		}
	}
	if (!seen[t]) return false;

	int c = res[prev[t]][t];
	for (int x = t; x != s; x = prev[x])
		c <?= res[prev[x]][x];

	for (int x = t; x != s; x = prev[x]) {
		res[prev[x]][x] -= c;
		res[x][prev[x]] += c;

		flow[prev[x]][x] += c;
		flow[x][prev[x]] -= c;
	}

	return true;
}

int main() {
	int T, R, C, rsum[50], csum[50];
	int rv[50], cv[50];

	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		printf("Matrix %d\n", cs);

		scanf("%d %d", &R, &C);
		REP(i,R) scanf("%d", &rsum[i]);
		REP(i,C) scanf("%d", &csum[i]);

		for (int i = R-1; i > 0; i--) rsum[i] -= rsum[i-1];
		for (int i = C-1; i > 0; i--) csum[i] -= csum[i-1];

		int lower = 1, upper = 20;
		REP(r,R) rsum[r] -= C*lower;
		REP(c,C) csum[c] -= R*lower;

		int s=0, t=1;
		N = 2;
		REP(r,R) rv[r] = N++;
		REP(c,C) cv[c] = N++;

		memset(res, 0, sizeof(res));
		REP(r,R) res[s][rv[r]] += rsum[r];
		REP(c,C) res[cv[c]][t] += csum[c];
		REP(r,R) REP(c,C) res[rv[r]][cv[c]] += upper - lower;

		memset(flow, 0, sizeof(flow));
		while (aug(s, t));

		REP(r,R) {
			REP(c,C) printf(c?" %d":"%d", lower + flow[rv[r]][cv[c]]);
			printf("\n");
		}
		printf("\n");
	}
}

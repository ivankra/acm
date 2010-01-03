#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(V,N) for(int V=0,REP_N=(int)(N);V<REP_N;V++)
#define INF 0x3fffffff

int d[128][128], cost[128][128], road[128][128], use[128*128], N, M;

// d[i][j] = length of shortest path between i and j
// road[i][j] = # of cheapest edge between and i and j, or -1 if there's no edge
// cost[i][j] = cost of cheapest edge between i and j, if there's any
// use[e] = how many ordered pairs of integers i, j there exists, such that
//   edge with index e lies on some shortest path between vertices i and j.

int main() {
	while (scanf("%d %d", &N, &M) == 2) {
		// initialization
		REP(i,N) REP(j,N) { d[i][j]=i==j?0:INF; road[i][j]=-1; }

		// read in edges
		REP(i,M) {
		       int x, y, c;
		       scanf("%d %d %d", &x, &y, &c);
		       x--; y--;
		       if (c < d[x][y]) {
			       d[x][y] = d[y][x] = c;
			       cost[x][y] = cost[y][x] = c;
			       road[x][y] = road[y][x] = i;
		       }
		       use[i] = 0;
		}

		// floyd-warshall
		REP(k,N) REP(i,N) REP(j,N) d[i][j] <?= d[i][k] + d[k][j];

		// consider every starting vertex s.
		REP(s,N) {
			// for each 0<=i<N, compute b[i] = number of vertices t,
			// such that vertex i is an intermediate vertex on a
			// shortest path from s to t.
			int b[128];
			REP(i,N) {
				b[i] = 0;
				REP(t,N) b[i] += d[s][i]+d[i][t]==d[s][t];
			}

			// for each edge (i, j)...
			REP(i,N) REP(j,N) if (road[i][j] >= 0)
				// if this edge lies on a shortest path from s to j...
 				if (d[s][i]+cost[i][j] == d[s][j])
					// increment its usage by b[j]
					use[road[i][j]] += b[j];
		}

		// print out maximally used edges
		int max_use = *max_element(use, use+M), k = 0;
		REP(i,M) if (use[i] == max_use) printf(k++ ? " %d" : "%d", i+1);
		printf("\n");
	}
}

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int adj[256][256], label[256][256], N;
int dist[256][256], next[256][256];
map<int, int> mp;

int offer[50][50], offerK[50], offerCost[50], M;

int memo[50][50], V[50], K;

int f(int pos, int s) {
	int &res = memo[pos][s];
	if (res != -1) return res;

	if (pos >= K-1) return res = dist[s][V[K-1]];

	res = 0x1fffffff;

	for (int o = 0; o < M; o++) {
		res <?= dist[s][V[pos]] + f(pos+1, V[pos]);
		for (int i = 0; i < offerK[o]; i++) {
			if (offer[o][i] != V[pos]) continue;
			for (int p = pos, j = i; j < offerK[o]; j++) {
				if (offer[o][j] == V[p] && p < K) p++;
				res <?= dist[s][offer[o][0]] + offerCost[o] + f(p, offer[o][j]);
			}
		}
	}

	return res;
}

void path(int x, int y, vector<int> &res) {
	while (x != y) {
		res.push_back(label[x][next[x][y]]);
		x = next[x][y];
	}
}

void recover(int pos, int s, vector<int> &out) {
	if (pos >= K-1) { path(s, V[K-1], out); return; }

	int res = f(pos, s);
	for (int o = 0; o < M; o++) {
		if (res == dist[s][V[pos]] + f(pos+1, V[pos])) {
			path(s, V[pos], out);
			recover(pos+1, V[pos], out);
			return;
		}

		for (int i = 0; i < offerK[o]; i++) {
			if (offer[o][i] != V[pos]) continue;
			for (int p = pos, j = i; j < offerK[o]; j++) {
				if (offer[o][j] == V[p] && p < K) p++;
				if (res == dist[s][offer[o][0]] + offerCost[o] + f(p, offer[o][j])) {
					path(s, offer[o][0], out);
					out.push_back(o+1);
					recover(p, offer[o][j], out);
					return;
				}
			}
		}
	}
}


int main() {
	for (int cs = 1; scanf("%d", &M) == 1 && M > 0; cs++) {
		memset(adj, 0x1f, sizeof(adj));
		for (int i = 0; i < 256; i++) adj[i][i] = 0;

		mp.clear();
		N = 0;

		for (int of = 0; of < M; of++) {
			scanf("%d %d", &offerCost[of], &offerK[of]);
			for (int i = 0; i < offerK[of]; i++) {
				int v;
				scanf("%d", &v);
				if (mp.count(v) == 0) mp[v] = N++;
				v = mp[v];
				offer[of][i] = v;
			}

			for (int i = 1; i < offerK[of]; i++) {
				int x = offer[of][0], y = offer[of][i];
				if (offerCost[of] < adj[x][y]) {
					adj[x][y] = offerCost[of];
					label[x][y] = of+1;
				}
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				dist[i][j] = (i == j ? 0 : adj[i][j]);
				next[i][j] = j;
			}
		}

		for (int k = 0; k < N; k++) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (dist[i][k] + dist[k][j] < dist[i][j]) {
						dist[i][j] = dist[i][k] + dist[k][j];
						next[i][j] = next[i][k];
					}
				}
			}
		}

		int Q;
		scanf("%d", &Q);

		for (int q = 1; q <= Q; q++) {
			scanf("%d", &K);
			for (int i = 0; i < K; i++) {
				scanf("%d", &V[i]);
				V[i] = mp[V[i]];
			}

			memset(memo, 0xff, sizeof(memo));
			printf("Case %d, Trip %d: Cost = %d\n", cs, q, f(0, V[0]));

			vector<int> res;
			recover(0, V[0], res);
			//res.erase(unique(res.begin(), res.end()), res.end());

			printf("  Tickets used:");
			for (int i = 0; i < (int)res.size(); i++)
				printf(" %d", res[i]);
			printf("\n");
		}
	}
}


/*

3 
225 3 1 3 4 
200 2 1 2 
50 2 2 3 
1 
2 1 3 


3 
100 2 2 4 
100 3 1 4 3 
200 3 1 2 3 
3 
3 1 4 3 
3 1 2 4 
2 1 3

2
100 6  1 2 3 4 5 6
10 4   5 7 8 9
1
4  1 3 7 8

1
100 4  1 2 3 1
1
3  1 3 2

0
*/
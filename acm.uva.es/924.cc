#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

#define INF 1000000

int N;
int deg[2600], adj[2600][16];
int dist[2600], cnt[2600];

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &deg[i]);
		for (int j = 0; j < deg[i]; j++)
			scanf("%d", &adj[i][j]);	
	}

	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		int source;
		scanf("%d", &source);

		for (int i = 0; i < N; i++) dist[i] = INF;
		dist[source] = 0;

		vector<int> q(1, source);
		for (int head = 0; head < (int)q.size(); head++) {
			int x = q[head];
			for (int i = 0; i < deg[x]; i++) {
				int y = adj[x][i];
				if (dist[y] == INF) {
					dist[y] = dist[x] + 1;
					q.push_back(y);
				}
			}
		}

		if (q.size() == 1) {
			printf("0\n");
			continue;
		}

		memset(cnt, 0, sizeof(cnt));
		for (int x = 0; x < N; x++)
			if (dist[x] != INF) cnt[dist[x]]++;

		int M = 0, D = 0;
		for (int d = 1; d <= N; d++) {
			if (cnt[d] > M) {
				M = cnt[d];
				D = d;
			}
		}

		printf("%d %d\n", M, D);
	}
}

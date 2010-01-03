#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int N, A, B, cycle[3010], seen[3010], counter;
vector<int> adj[3010];
int dist[2][3010];

int dfs(int x, int parent)
{
    int low = INT_MAX;
    seen[x] = ++counter;

    for (int i = 0; i < (int)adj[x].size(); i++) {
	int y = adj[x][i];
	if (y == parent) continue;
	if (seen[y] == 0) {
	    low = min(low, dfs(y, x));
	} else if (seen[y] <= seen[x]) {
	    low = min(low, seen[y]);
	}
    }

    cycle[x] = (low <= seen[x]);
    return low;
}


int main()
{
    int T, M, x, y, i, j;
    scanf("%d", &T);

    for (int cs = 1; cs <= T; cs++) {
	scanf("%d %d %d %d", &N, &M, &A, &B);
	for (i = 0; i <= N; i++) adj[i].clear();
	for (i = 0; i < M; i++) {
	    scanf("%d %d", &x, &y);
	    adj[x].push_back(y);
	    adj[y].push_back(x);
	}

	memset(cycle, 0, sizeof(cycle));
	memset(seen, 0, sizeof(seen));
	counter = 1;
	dfs(1, -1);

	memset(dist, 0x3f, sizeof(dist));
	for (i = 0; i < 2; i++) {
	    queue<int> q;
	    q.push(i == 0 ? A : B);
	    dist[i][q.front()] = 0;

	    while (!q.empty()) {
		x = q.front(); q.pop();
		for (j = 0; j < (int)adj[x].size(); j++) {
		    y = adj[x][j];
		    if (dist[i][x] + 1 < dist[i][y]) {
			dist[i][y] = dist[i][x] + 1;
			q.push(y);
		    }
		}
	    }
	}

	int res = -1;
	for (x = 1; x <= N; x++) {
	    if (cycle[x] && dist[0][x] < dist[1][x]) {
		printf("No\n");
		goto done;
	    }
	    if (adj[x].size() == 1 && dist[0][x] < dist[1][x]) {
		res = max(res, dist[1][x]);
	    }
	}
	assert(res != -1);
	printf("%d\n", res);
done:;
    }
}

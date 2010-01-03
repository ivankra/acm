#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long int64;

#define MAXN 512

struct Vertex {
	int64 x, y;
	int64 radius;
	int64 range;

	int64 DistanceTo(const Vertex &v) const {
		return (v.x-x)*(v.x-x)+(v.y-y)*(v.y-y);
	}
};

struct SCC {
	int rep;
	int in, out;
	int64 cost;
};

int S;
SCC scc[MAXN];

bool byCost(int i, int j) {
	if (scc[i].cost != scc[j].cost) return scc[i].cost < scc[j].cost;
	return scc[i].rep < scc[j].rep;
}

bool byOut(int i, int j) {
	if (scc[i].out != scc[j].out) return scc[i].out < scc[j].out;
	return scc[i].rep < scc[j].rep;
}

void SolveDAG() {
	int a[MAXN], k = 0;
	for (int i = 0; i < S; i++)
		if (scc[i].in == 0) a[k++] = i;

	for (int i = 0, t = k; i < S; i++)
		if (scc[i].in > 0) a[t++] = i;

	sort(a+k, a+S, byCost);

	int64 sum = 0;
	for (int i = 0; i < k; i++)
		sum += scc[a[i]].cost;

	int64 bestK = k, bestSum = sum;
	while (k < S) {
		sum += scc[a[k]].cost;
		k++;
		if (sum*bestK < bestSum*k) {
			bestSum = sum;
			bestK = k;
		}
	}

	sort(a, a+bestK, byOut);
	for (int i = 0; i < bestK; i++)
		printf(" %d", scc[a[i]].rep);
	printf("\n");
}

void Solve(Vertex V[], int N) {
	static bool adj[MAXN][MAXN];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int64 a = V[i].range + V[i].radius + V[j].radius;
			int64 b = V[i].DistanceTo(V[j]);
			adj[i][j] = (a >= b || a*a >= b);
		}
		adj[i][i] = true;
	}

	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			if (adj[i][k])
				for (int j = 0; j < N; j++)
					adj[i][j] |= adj[k][j];

	int sccOf[MAXN];
	for (int i = 0; i < N; i++)
		sccOf[i] = -1;

	S = 0;
	for (int x = 0; x < N; x++) {
		if (sccOf[x] < 0) {
			scc[S].rep = x;
			scc[S].in = scc[S].out = 0;
			for (int y = 0; y < N; y++) {
				if (adj[x][y] && adj[y][x]) {
					sccOf[y] = S;
					if (V[y].range < V[scc[S].rep].range)
						scc[S].rep = y;
				}
			}
			scc[S].cost = V[scc[S].rep].range;
			S++;
		}
	}

	for (int i = 0; i < S; i++) {
		for (int j = 0; j < S; j++) {
			if (i != j && adj[scc[i].rep][scc[j].rep]) {
				scc[i].out++;
				scc[j].in++;
			}
		}
	}

	SolveDAG();
}

int main() {
	Vertex V[MAXN];
	int N, T;
	assert(scanf("%d", &T) == 1);

	for (int cs = 1; cs <= T; cs++) {
		assert(scanf("%d", &N) == 1);
		assert(1 <= N && N < MAXN);

		for (int i = 0; i < N; i++) {
			int t = scanf("%lld %lld %lld %lld", 
				&V[i].x, &V[i].y,
				&V[i].radius, &V[i].range);
			assert(t == 4);
			assert(V[i].radius >= 0);
			assert(V[i].range >= 0);
		}

		printf("Case #%d:", cs);
		Solve(V, N);
	}
}

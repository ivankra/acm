#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int nroads;
struct Road {
	int a, b;
	double len;
} roads[15000];

struct Edge {
	int y;
	double c;
	Edge(int Y, double C) : y(Y), c(C) {}
};

int N;
vector<Edge> G[15000];

double vdist[15000];
int heap[15000], idx[15000], heap_size;

void heapup(int k) {
	int x = heap[k];
	for (; k > 1 && vdist[heap[k>>1]] > vdist[x]; k >>= 1)
		idx[heap[k] = heap[k>>1]] = k;
	idx[heap[k] = x] = k;
}

void heapdown(int x) {
	while (2*x <= heap_size) {
		int y = 2*x;
		if (y+1 <= heap_size && vdist[heap[y+1]] < vdist[heap[y]]) y++;

		if (vdist[heap[x]] < vdist[heap[y]]) break;

		swap(heap[x], heap[y]);
		idx[heap[x]] = x;
		idx[heap[y]] = y;
		x = y;
	}
}

bool dijkstra(int src, int dst) {
	int prev[15000];

	for (int i = 0; i < N; i++) idx[i] = -1;
	for (int i = 0; i < N; i++) vdist[i] = -1;
	for (int i = 0; i < N; i++) prev[i] = -1;
	heap[heap_size = 1] = src;
	idx[src] = 1;
	vdist[src] = 0;

	while (heap_size > 0) {
		int x = heap[1];
		idx[x] = -1;
		if (--heap_size > 0) {
			idx[heap[1] = heap[heap_size+1]] = 1;
			heapdown(1);
		}

//		printf("x=%d (prev=%d): dist=%.5f\n", x, prev[x], vdist[x]);

		for (int i = 0; i < (int)G[x].size(); i++) {
			int y = G[x][i].y;
			if (vdist[y] < 0 || vdist[x] + G[x][i].c < vdist[y] - 1e-8) {
				vdist[y] = vdist[x] + G[x][i].c;
				if (idx[y] < 0) {
					idx[y] = ++heap_size;
					heap[heap_size] = y;
				}
				prev[y] = x;
				heapup(idx[y]);
			}
		}
	}

	if (vdist[dst] < 0) return false;

	printf("%.3f\n", vdist[dst]);

	vector<int> path;
	for (int i = dst; i != src; i = prev[i])
		path.push_back(roads[i].a);

	for (int i = path.size()-1; i >= 0; i--)
		printf(i==0 ? "%d\n" : "%d ", path[i]+1);

	return true;
}

int main()
{
	int T;
	scanf("%d", &T);

	vector<int> adj[1024], adj_rev[1024];
	double cx[1024], cy[1024];

	double PI = 2 * acos(0.0);

	for (int cs = 1; cs <= T; cs++) {
		if (cs > 1) printf("\n");

		int ncities, city1, city2;
		double coef;

		scanf("%d %d %d %d %lf", &ncities, &nroads, &city1, &city2, &coef);
		city1--;
		city2--;

		for (int i = 0; i < ncities; i++)
			scanf("%lf %lf", &cx[i], &cy[i]);

		for (int i = 0; i < ncities; i++) {
			adj[i].clear();
			adj_rev[i].clear();
		}

		for (int i = 0; i < nroads; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			a--; b--;
			adj[a].push_back(i);
			adj_rev[b].push_back(i);
			roads[i].a = a;
			roads[i].b = b;
			roads[i].len = sqrt((cx[a]-cx[b])*(cx[a]-cx[b])+(cy[a]-cy[b])*(cy[a]-cy[b]));
		}

		N = 2 + nroads;
		for (int i = 0; i < N; i++) G[i].clear();

		int src = nroads;
		int dst = nroads + 1;

		roads[src].a = roads[src].b = city1;
		roads[dst].a = roads[dst].b = city2;

		for (int i = 0; i < (int)adj[city1].size(); i++) {
			int r = adj[city1][i];
			G[src].push_back(Edge(r, roads[r].len/2));
//			printf("src-%d: %.5f\n", r, roads[r].len/2);
		}

		for (int i = 0; i < (int)adj_rev[city2].size(); i++) {
			int r = adj_rev[city2][i];
			G[r].push_back(Edge(dst, roads[r].len/2));
//			printf("%d-dst: %.5f\n", r, roads[r].len/2);
		}

		for (int a = 0; a < ncities; a++) {
			for (int i = 0; i < (int)adj[a].size(); i++) {
				int r1 = adj[a][i], b = roads[r1].b;
				for (int j = 0; j < (int)adj[b].size(); j++) {
					int r2 = adj[b][j], c = roads[r2].b;
					if (a == c) continue;

					double ang = (cx[c]-cx[b])*(cx[a]-cx[b]) + (cy[c]-cy[b])*(cy[a]-cy[b]);
					ang = -ang;
					ang /= roads[r1].len;
					ang /= roads[r2].len;
					if (ang > 1.0) ang = 1.0;
					if (ang < -1.0) ang = -1.0;

					ang = acos(ang) / PI * 180.0;

					double dist = roads[r1].len/2 + roads[r2].len/2 + coef * ang;
					G[r1].push_back(Edge(r2, dist));

//					printf("%d-%d: %.5f  (angle=%.3fdeg)\n", r1,r2,dist,ang);
				}
			}
		}

		if (!dijkstra(src, dst)) {
			printf("Impossible\n");
		}
	}
}

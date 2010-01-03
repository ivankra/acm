// Algorithm: the optimal path consists of tangents between source/destination points,
// tangents between circles, and also circle segments which join tangent points.
// Tags: geometry, nice, graph
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

double PI = 2 * acos(0.0);
double INF = 1.0 / 0.0;
double EPS = 1e-9;

struct Point {
	double x, y;
};

struct Circle {
	Point o;
	double r;
	vector<int> arc;
} C[20];

Point V[512];
double adj[512][512];
int N, K;

double dist(const Point &a, const Point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double cross(const Point &o, const Point &a, const Point &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

bool visible(const Point &a, const Point &b) {
	if (dist(a, b) < EPS) return true;
	for (int i = 0; i < K; i++) {
		const Circle &c = C[i];
		const Point &o = c.o;
		double h = fabs(cross(a, b, o)) / dist(a, b);
		if (h < c.r - EPS) {
			double t = (o.x - a.x) * (b.x - a.x) + (o.y - a.y) * (b.y - a.y);
			double s = (o.x - b.x) * (a.x - b.x) + (o.y - b.y) * (a.y - b.y);
			if (t > EPS && s > EPS)
				return false;
		}
	}
	return true;
}

void buildGraph()
{
	// Line of sight between source and destination
	if (visible(V[0], V[1])) {
		adj[0][1] = adj[1][0] = dist(V[0], V[1]);
		return;
	}

	// Tangents from source/destination to each circle
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < K; j++) {
			Point p = V[i];
			Circle c = C[j];

			double alpha = atan2(p.y - c.o.y, p.x - c.o.x);
			double delta = acos(c.r / dist(p, c.o));

			for (int sign = -1; sign <= 1; sign += 2) {
				Point q;
				q.x = c.o.x + c.r * cos(alpha + sign * delta);
				q.y = c.o.y + c.r * sin(alpha + sign * delta);

//printf("(%.2f, %.2f) -> circle %.2f, %.2f, r=%.2f: tangent point %.2f %.2f\n",p.x, p.y, c.o.x, c.o.y, c.r, q.x, q.y);

				if (visible(p, q)) {
					C[j].arc.push_back(N);
					V[N] = q;
					adj[i][N] = adj[N][i] = dist(p, q);
					N++;
				}
			}
		}
	}

	// Tangent points at circles
	for (int ci = 0; ci < K; ci++) {
		for (int cj = 0; cj < K; cj++) {
			if (ci == cj) continue;

			Point A = C[ci].o;
			Point B = C[cj].o;
			double phi = atan2(B.y - A.y, B.x - A.x);

			for (int sign = -1; sign <= 1; sign += 2) {
				double cs = (C[ci].r + sign * C[cj].r) / dist(A, B);
				if (cs > 1.0) cs = 1.0;
				if (cs < -1.0) cs = -1.0;

				double delta = acos(cs);

				for (int sign2 = -1; sign2 <= 1; sign2 += 2) {
					Point P;
					P.x = A.x + C[ci].r * cos(phi + sign2 * delta);
					P.y = A.y + C[ci].r * sin(phi + sign2 * delta);

					C[ci].arc.push_back(N);
					V[N++] = P;

//printf("circle %.2f, %.2f, r=%.2f: tangent point %.2f, %.2f\n",	C[ci].o.x, C[ci].o.y, C[ci].r, P.x, P.y);

					if (fabs(delta) < EPS) break;
				}
			}
		}
	}

	// Tangents between circles
	for (int i = 2; i < N; i++) {
		for (int j = i+1; j < N; j++) {
			if (visible(V[i], V[j])) {
//				printf("%.2f, %.2f - %.2f, %.2f\n", V[i].x, V[i].y, V[j].x, V[j].y);
				adj[i][j] = adj[j][i] = dist(V[i], V[j]);
			}
		}
	}

	// Circular segments
	for (int i = 0; i < K; i++) {
		int *a = &C[i].arc[0];
		int m = C[i].arc.size();
		for (int j = 0; j < m; j++) {
			for (int k = j+1; k < m; k++) {
				double t = (V[a[j]].x - C[i].o.x) * (V[a[k]].x - C[i].o.x);
				t += (V[a[j]].y - C[i].o.y) * (V[a[k]].y - C[i].o.y);
				t /= C[i].r * C[i].r;
				if (t < -1) t = -1;
				if (t > 1) t = 1;
				t = acos(t);

//				printf("%.2f, %.2f - %.2f, %.2f: circular segment %.5f\n",
//					V[a[j]].x, V[a[j]].y,
//					V[a[k]].x, V[a[k]].y, t*C[i].r);
				adj[a[j]][a[k]] = adj[a[k]][a[j]] = t * C[i].r;
			}
		}
	}

	for (int i = 0; i < N; i++)
		adj[i][i] = 0;
}

double dijkstra()
{
	double dist[512];
	int seen[512];

	memset(seen, 0, sizeof(seen));

	for (int i = 0; i < N; i++)
		dist[i] = INF;
	dist[0] = 0;

	for (;;) {
		int u = -1;
		for (int i = 0; i < N; i++)
			if (seen[i] == 0 && (u < 0 || dist[i] < dist[u])) u = i;

		if (u < 0 || u == 1) break;

		seen[u] = 1;
		for (int v = 0; v < N; v++)
			dist[v] <?= dist[u] + adj[u][v];
	}

	return dist[1];
}

int main() {
	int T;
	scanf("%d", &T);

	N = 512;

	for (int cs = 1; cs <= T; cs++) {
		if (cs != 1) printf("\n");

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				adj[i][j] = INF;

		scanf("%d %lf %lf %lf %lf", &K, &V[0].x, &V[0].y, &V[1].x, &V[1].y);
		N = 2;

		for (int i = 0; i < K; i++) {
			scanf("%lf %lf %lf", &C[i].o.x, &C[i].o.y, &C[i].r);
			C[i].r /= 2;
			C[i].arc.clear();
		}

		buildGraph();
		printf("%.2f\n", dijkstra() * 3600.0 / 200.0);
	}
}

#include <algorithm>
#include <vector>
#include <sstream>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cctype>
using namespace std;

struct Point {
	int x, y;

	bool operator <(const Point &p) const { return x < p.x || (x == p.x && y < p.y); }
	bool operator ==(const Point &p) const { return x == p.x && y == p.y; }
};

void read(Point &p) {
	char c;
	scanf(" %c %d", &c, &p.x);
	p.y = toupper(c) - 'A' + 1;
}

bool on(const Point &p, const Point &a, const Point &b) {
	int t = (a.x-p.x)*(b.y-p.y) - (a.y-p.y)*(b.x-p.x);
	if (t != 0) return false;

	if (p.x < min(a.x, b.x) || p.x > max(a.x, b.x)) return false;
	if (p.y < min(a.y, b.y) || p.y > max(a.y, b.y)) return false;
	return true;
}

Point P[256];
int N, adj[32][32];
double fw[32][32];

int seen[32];
int dfs(int x) {
	if (seen[x]++) return 0;
	int c = 1;
	for (int i = 0; i < N; i++)
		if (adj[x][i]) c += dfs(i);
	return c;
}

int odd[32], nodd;
int got[1<<18], got_id;
double memo[1<<18];

double match(int mask) {
	if (mask == 0) return 0.0;
	double &res = memo[mask];
	if (got[mask] == got_id) return res;
	got[mask] = got_id;

	int a;
	for (a = 0; (mask & (1 << a)) == 0; a++);

	res = 1e99;
	for (int b = a+1; b < nodd; b++) {
		if ((mask & (1 << b)) != 0) {
			res <?= fw[odd[a]][odd[b]] + match(mask ^ (1<<a) ^ (1<<b));
		}
	}
	return res;
}

void load() {
	int nseg;
	Point segA[32], segB[32];

	scanf("%d", &nseg);
	assert(0 <= nseg && nseg <= 10);

	for (int i = 0; i < nseg; i++) {
		read(segA[i]);
		read(segB[i]);
	}

	N = 0;
	for (int i = 0; i < nseg; i++) {
		P[N++] = segA[i];
		P[N++] = segB[i];
	}

	for (int x = 1; x <= 5; x++) {
		for (int y = 1; y <= 5; y++) {
			Point p; p.x = x; p.y = y;
			bool add = false;
			for (int k = 0; k < nseg; k++) {
				for (int m = k+1; m < nseg; m++) {
					if (!on(p, segA[k], segB[k])) continue;
					if (!on(p, segA[m], segB[m])) continue;

					if (on(segA[k],  segA[m], segB[m])) continue;
					if (on(segB[k],  segA[m], segB[m])) continue;
					if (on(segA[m],  segA[k], segB[k])) continue;
					if (on(segB[m],  segA[k], segB[k])) continue;

					add = true;
				}
			}
			if (add) P[N++] = p;
		}
	}

	sort(P, P+N);
	N = unique(P, P+N) - P;

	memset(adj, 0, sizeof(adj));
	for (int i = 0; i < nseg; i++) {
		if (segA[i] == segB[i]) continue;

		int a, b;
		for (a = 0; !(P[a] == segA[i]); a++);
		for (b = 0; !(P[b] == segB[i]); b++);

		vector<int> v;
		for (int k = 0; k < N; k++)
			if (on(P[k], P[a], P[b])) v.push_back(k);

		for (int i = 0; i < (int)v.size(); i++)
			for (int j = i+1; j < (int)v.size(); j++)
				adj[v[i]][v[j]] = adj[v[j]][v[i]] = 1;
	}

	for (int a = 0; a < N; a++) {
		adj[a][a] = 0;
		for (int b = a+1; b < N; b++) {
			if (!adj[a][b]) continue;

			for (int c = 0; c < N; c++) {
				if (c != a && c != b && on(P[c], P[a], P[b])) {
					adj[a][b] = adj[b][a] = 0;
					break;
				}
			}

//			if (adj[a][b])printf("%d,%d - %d,%d\n", P[a].x, P[a].y, P[b].x, P[b].y);
		}
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	memset(got, 0, sizeof(got));

	for (int cs = 1; cs <= T; cs++) {
		load();

		memset(seen, 0, sizeof(seen));
		if (N > 0 && dfs(0) != N) {
			printf("Case %d: ~x(\n", cs);
			continue;
		}

		double ans = 0;

		nodd = 0;

		for (int a = 0; a < N; a++) {
			int deg = 0;
			for (int b = 0; b < N; b++) {
				deg += adj[a][b];
				if (adj[a][b]) {
					fw[a][b] = sqrt(0.0 + (P[a].x-P[b].x)*(P[a].x-P[b].x) + (P[a].y-P[b].y)*(P[a].y-P[b].y));
					if (a < b) ans += fw[a][b];
				} else {
					fw[a][b] = (a==b ? 0 : 1e99);
				}
			}

			if (deg % 2 != 0)
				odd[nodd++] = a;
		}

		for (int k = 0; k < N; k++)
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					fw[i][j] <?= fw[i][k] + fw[k][j];

		got_id++;
		if (nodd > 0) {
			assert(nodd%2 == 0 && nodd <= 18);

			double t = 1e99;
			for (int i = 0; i < nodd; i++)
				for (int j = i+1; j < nodd; j++)
					t <?= match(((1<<nodd)-1) ^ (1 << i) ^ (1 << j));
			ans += t;
		}

		printf("Case %d: %.2f\n", cs, ans);
	}
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

struct Frac {
	long long p, q;	

	inline void reduce() {
		if (q < 0) { p = -p; q = -q; }
		if (q == 0) { p = 1; return; }

		long long g = __gcd(p, q);
		p /= g; q /= g;
	}

	Frac(long long p = 0, long long q = 1) : p(p), q(q) { reduce(); }

	Frac operator *(const Frac &b) const { return Frac(p * b.p, q * b.q); }
	Frac operator /(const Frac &b) const { return Frac(p * b.q, q * b.p); }
	Frac operator +(const Frac &b) const { return Frac(p * b.q + b.p * q, q * b.q); }
	Frac operator -(const Frac &b) const { return Frac(p * b.q - b.p * q, q * b.q); }

	void operator /=(const Frac &b) { p *= b.q; q *= b.p; reduce(); }
	void operator -=(const Frac &b) { p = p * b.q - b.p * q; q *= b.q; reduce(); }

	bool operator ==(const Frac &b) const { return p*b.q == q*b.p; }
	bool isZero() const { return p == 0 && q != 0; }
	bool isInf() const { return p != 0 && q == 0; }
};

Frac abs(const Frac &a) { return Frac(a.p < 0 ? -a.p : a.p, a.q); }

int dim;
Frac mat[140][140];

void gauss() {
#if 0
	printf("input matrix\n");
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j <= dim; j++)
			printf(mat[i][j].q==1?"%lld ":"%lld/%lld ", mat[i][j].p, mat[i][j].q);
		printf("\n");
	}
#endif

	for (int row = 0; row < dim; row++) {
		int bestRow = row;
		for (int i = row; i < dim; i++) {
			if (mat[i][row].isZero()) continue;
			bestRow = i;
			break;
		}

		if (mat[bestRow][row].isZero()) {
			//printf("matrix is singular\n");
			return;
		}

		if (bestRow != row) {
			for (int i = row; i <= dim; i++) {
				swap(mat[bestRow][i].p, mat[row][i].p);
				swap(mat[bestRow][i].q, mat[row][i].q);
			}
		}

		for (int i = dim; i > row; i--)
			mat[row][i] /= mat[row][row];
		mat[row][row] = 1;

		for (int r = row+1; r < dim; r++) {
			if (!mat[r][row].isZero()) {
				for (int i = dim; i > row; i--)
					mat[r][i] -= mat[r][row] * mat[row][i];
				mat[r][row] = 0;
			}
		}
	}

#if 0
	printf("gauss: output\n");
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j <= dim; j++)
			printf(mat[i][j].q==1?"%lld ":"%lld/%lld ", mat[i][j].p, mat[i][j].q);
		printf("\n");
	}
#endif
}

int N;
Frac adj[32][32], INF(1,0);

void dfs(int x, int seen[]) {
	if (seen[x] != -1) return;
	seen[x] = -2;

	for (int y = 0; y < N; y++)
		if (!adj[x][y].isInf())
			dfs(y, seen);
}

Frac solve(int s, int t) {
	if (s == t) return 0;

	int id[32];
	memset(id, 0xff, sizeof(id));
	dfs(s, id);
	if (id[t] == -1) return INF;

	id[s] = 0;
	id[t] = 1;
	int K = 2;

	for (int i = 0; i < N; i++)
		if (id[i] == -2) id[i] = K++;

	int edgeId[16][16];
	memset(edgeId, 0xff, sizeof(edgeId));

	int M = 0;
	for (int x = 0; x < N; x++) {
		for (int y = x+1; y < N; y++) {
			if (id[x] < 0 || id[y] < 0 || adj[x][y].isInf()) continue;
			edgeId[x][y] = edgeId[y][x] = M++;
		}
	}

	dim = K+M + 1;
	assert(dim <= 139);

	for (int i = 0; i < dim; i++)
		for (int j = 0; j <= dim; j++)
			mat[i][j] = 0;

	// K+M+1 vars (currents, potentials, goal)
	// M+(K-2)+2 + 1 eq  (ohm's;  conservation of pot. - potentials of s and t, goal eq)

	int eq = 0;
	mat[eq][0] = 1; eq++;                    // V0 = 0
	mat[eq][1] = 1; mat[eq][dim] = 1; eq++;  // V1 = 1

	for (int x = 0; x < N; x++) {
		if (id[x] < 0) continue;

		for (int y = x+1; y < N; y++) {
			if (id[y] < 0 || adj[x][y].isInf()) continue;

			// V[y] - V[x] = R*I[xy]
			mat[eq][id[y]] = 1;
			mat[eq][id[x]] = -1;
			mat[eq][K+edgeId[x][y]] = Frac(0) - adj[x][y];
			eq++;
		}

		if (x != t) {
			// sum_y I(xy) = 0  for x!=s, x!=t
			for (int y = 0; y < N; y++) {
				if (id[y] < 0 || x == y || adj[x][y].isInf()) continue;
				mat[eq][K+edgeId[x][y]] = (y < x ? -1 : 1);
			}

			if (x == s) {
				// sum_y I(sy) = voltage between s and t
				mat[eq][K+M] = -1;
			}

			eq++;
		}
	}

	assert(dim == eq);

	gauss();

	Frac I = abs(mat[K+M][dim]);
	if (I.isZero()) return INF;
	return Frac(1) / I;
}

int main() {
	int T, M;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d %d", &N, &M) == 2; cs++) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				adj[i][j] = (i == j ? 0 : INF);

		for (int i = 0; i < M; i++) {
			int x, y, r;
			scanf("%d %d %d", &x, &y, &r);

			if (adj[x][y].isInf())
				adj[y][x] = adj[x][y] = r;
			else
				adj[y][x] = adj[x][y] = (adj[x][y] * r) / (adj[x][y] + r);
		}

		printf("Case #%d:\n", cs);

#if 0
		for (int i = 0; i < N; i++)
			for (int j = j+1; j < N; j++)
				if (!adj[i][j].isInf())
					printf("%d-%d %lld/%lld\n", i, j, adj[i][j].p, adj[i][j].q);
#endif

		int Q;
		scanf("%d", &Q);

		for (int i = 0; i < Q; i++) {
			int s, t;
			scanf("%d %d", &s, &t);

			Frac res = solve(s, t);
			printf("Resistance between %d and %d is %lld/%lld\n", s, t, res.p, res.q);
		}

		printf("\n");
	}
}

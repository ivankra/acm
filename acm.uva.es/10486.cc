#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct UnionFind {
	int p[2000], r[2000], s[2000];
	int maxSize;

	void init(int N) {
		for (int i = 0; i <= N; i++) p[i] = i;
		for (int i = 0; i <= N; i++) r[i] = 0;
		for (int i = 0; i <= N; i++) s[i] = 1;
		maxSize = 1;
	}

	int f(int x) {
		int y = p[x], z;
		while (p[y] != y) y = p[y];
		while (p[x] != y) { z = p[x]; p[x] = y; x = z; }
		return y;
	}

	void u(int x, int y) {
		x = f(x);
		y = f(y);
		if (x != y) {
			if (r[x] > r[y]) swap(x, y);
			p[x] = y;
			if (r[x] == r[y]) ++r[y];
			s[y] += s[x];
			if (s[y] > maxSize) maxSize = s[y];
		}
	}
} uf;

int mat[64][64], N, M;
int answer[2000];

int main()
{
	vector<pair<int, int> > v;

	scanf("%d %d", &N, &M);
	for (int i = 0; i < N*M; i++) {
		scanf("%d", &mat[i/M][i%M]);
		v.push_back(make_pair(mat[i/M][i%M], i));
	}

	memset(answer, 0x3f, sizeof(answer));
	answer[0] = answer[1] = 0;

	sort(v.begin(), v.end());
	for (int low = 0; low <= 100; low++) {
		uf.init(N*M);
		for (int i = 0; i < N*M; i++) {
			int y = v[i].second / M;
			int x = v[i].second % M;
			if (mat[y][x] < low) continue;

			for (int dir = 0; dir < 4; dir++) {
				int y1 = y + "0211"[dir] - '1';
				int x1 = x + "1102"[dir] - '1';
				if (y1 < 0 || y1 >= N || x1 < 0 || x1 >= M) continue;
				if (mat[y1][x1] < low) continue;
				if (mat[y1][x1] > mat[y][x]) continue;
				uf.u(y*M+x, y1*M+x1);
				answer[uf.maxSize] <?= mat[y][x] - low;
			}
		}
	}

	for (int i = N*M-1; i >= 1; i--)
		answer[i] = min(answer[i], answer[i+1]);

	int Q, size;
	for (scanf("%d", &Q); Q--;) {
		scanf("%d", &size);
		printf("%d\n", answer[size]);
	}
}

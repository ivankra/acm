#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
#define foreach(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

char dirName[] = "ENSW";
int dirR[4] = { 0, -1, 1, 0 }, dirC[4] = { 1, 0, 0, -1 }, dirMask[4] = { 4, 8, 2, 1 };

int N, wall[16][16], startR, startC, startPos;
int K, blueR[50], blueC[50], bluePos[50], blue[256];
int posR[256], posC[256], jumpTo[256][4], jumpMask[256][4];
int dist[256][256];
int estimateX[101][32], estimateXY[101][32][32];

bool valid(int r, int c) {
	return 0 <= r && r < N && 0 <= c && c < N;
}

struct State {
	int pos;
	int visited;
};

int IDA_limit, IDA_next, IDA_iter;
char path[1000];

map<int, int> seen;

bool dfs(State cur, int depth)
{
	State next;
	int estimate, i;

	++IDA_iter;

	if (blue[cur.pos] >= 0)
		cur.visited |= 1 << blue[cur.pos];

	if (cur.visited == (1 << K) - 1) {
		path[depth] = 0;
		return true;
	}

	estimate = 1;
	for (i = 0; i < K; i++) {
		if ((cur.visited & (1 << i)) != 0) continue;
		estimate = max(estimate, estimateX[cur.pos][i]);
	}

	if (depth + estimate > IDA_limit) {
		IDA_next = min(IDA_next, depth + estimate);
		return false;
	}

	i = (cur.visited << 7) | cur.pos;
	if (seen.count(i) != 0) {
		if (seen[i] <= depth) return false;
	}
	seen[i] = depth;

	for (i = 0; i < 4; i++) {
		next.pos = jumpTo[cur.pos][i];
		if (next.pos == cur.pos) continue;
		next.visited = cur.visited | jumpMask[cur.pos][i];
		path[depth] = dirName[i];
		if (dfs(next, depth + 1)) return true;
	}

	return false;
}

void solve()
{
	if (K == 0) {
		printf("\n");
		return;
	}

	memset(dist, 0x1f, sizeof(dist));
	for (int i = 0; i < N*N; i++) {
		posR[i] = i / N;
		posC[i] = i % N;
		for (int d = 0; d < 4; d++) {
			jumpMask[i][d] = 0;
			if (blue[i] >= 0)
				jumpMask[i][d] |= 1 << blue[i];

			int r = posR[i], c = posC[i];
			while (valid(r + dirR[d], c + dirC[d]) && (wall[r][c] & dirMask[d]) == 0) {
				r += dirR[d];
				c += dirC[d];
				int j = r*N + c;
				if (blue[j] >= 0)
					jumpMask[i][d] |= 1 << blue[j];
			}

			jumpTo[i][d] = r*N+c;
			dist[i][r*N+c] = 1;
		}
	}

	for (int k = 0; k < N*N; k++) {
		dist[k][k] = 0;
		for (int i = 0; i < N*N; i++) {
			for (int j = 0; j < N*N; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	for (int pos = 0; pos < N*N; pos++) {
		for (int x = 0; x < K; x++) {
			estimateX[pos][x] = 0x1fffffff;
			for (int j = 0; j < N*N; j++)
				for (int d = 0; d < 4; d++)
					if ((jumpMask[j][d] & (1 << x)) != 0) {
						estimateX[pos][x] = min(estimateX[pos][x], dist[pos][j] + (blue[j]==x?0:1));
					}
		}
	}

	IDA_iter = 0;
	IDA_limit = 1;
	while (true) {
		State s;
		s.pos = startPos;
		s.visited = 0;
		seen.clear();

		IDA_next = INT_MAX;
//printf("Current limit: %d\n", IDA_limit);
		if (dfs(s, 0)) {
			break;
		}

		assert(IDA_next < 1000000);
		assert(IDA_limit < 53);
		IDA_limit = min(53, IDA_next);
	}

//printf("Found path in total %d iterations\n", IDA_iter);

	printf("%s\n", path);
}

int main()
{
	char buf[10000];
	buf[0] = 0; gets(buf);
	while (true) {
		while (true) {
			N = 0;
			if (sscanf(buf, "%d", &N) == 1) break;
			if (gets(buf) == NULL) return 0;
		}
		if (N == 0) return 0;
		assert(2 <= N && N <= 10);

		for (int i = 0; i < N; i++) {
			{ char *s = gets(buf); assert(s != NULL); }
			for (int j = 0; j < N; j++) {
				char c = toupper(buf[j]);
				if (isalpha(c)) {
					assert('A' <= c && c <= 'F');
					wall[i][j] = toupper(c) - 'A' + 10;
				} else {
					assert('0' <= c && c <= '9');
					wall[i][j] = c - '0';
				}
			}
		}

		{ char *s = gets(buf); assert(s != NULL); }
		{ int i = sscanf(buf, "%d %d", &startR, &startC); assert(i == 2); }
		--startR; --startC;
		assert(valid(startR, startC));
		startPos = startR * N + startC;

		K = 0;
		memset(blue, 0xff, sizeof(blue));
		while (true) {
			buf[0] = 0;
			if (gets(buf) == NULL) break;
			if (sscanf(buf, "%d %d", &blueR[K], &blueC[K]) != 2) break;
			if (blueR[K] == 0 || blueC[K] == 0) break;
			--blueR[K]; --blueC[K];
			assert(valid(blueR[K], blueC[K]));
			bluePos[K] = blueR[K] * N + blueC[K];
			if (blue[bluePos[K]] < 0) {
				blue[bluePos[K]] = K;
				K++;
				assert(K <= 25);
			}
		}

		solve();
	}

	return 0;
}

// ACM ICPC World Finals 2007
// Problem F. Marble Game.
// Algorithm: breadth-first search.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <set>
#include <queue>
using namespace std;

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };
int may[4][4][4];
int N;
static inline bool valid(int y, int x) { return 0 <= y && y < N && 0 <= x && x < N; }

struct State {
	char a[4][4];
	int dist;

	string encode() {
#if 0
		string s;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (a[i][j] == 0) s += '.';
				else if (a[i][j] > 0) s += 'A' + a[i][j];
				else s += 'a' - a[i][j];
			}
			s += '\n';
		}
		return s;
#else
		string s;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				s += (char)(a[i][j]+60);
		return s;
#endif
	}

	bool solved() {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (a[i][j] != 0) return false;
		return true;
	}

	bool move(int dir) {
		for (int y0 = (dy[dir] > 0 ? N-1 : 0); 0 <= y0 && y0 < N; dy[dir] > 0 ? --y0 : ++y0) {
			for (int x0 = (dx[dir] > 0 ? N-1 : 0); 0 <= x0 && x0 < N; dx[dir] > 0 ? --x0 : ++x0) {
				if (a[y0][x0] <= 0) continue;

				int y = y0, x = x0;
				while (may[y][x][dir]) {
					int ch = a[y+dy[dir]][x+dx[dir]];
					if (ch == 0) {
						a[y+dy[dir]][x+dx[dir]] = a[y][x];
						a[y][x] = 0;
						y += dy[dir]; x += dx[dir];
					} else if (ch > 0) {
						break;
					} else if (ch == -a[y][x]) {
						a[y][x] = a[y+dy[dir]][x+dx[dir]] = 0;
						break;
					} else {
						return false;
					}
				}
			}
		}
		dist++;
		return true;
	}
};

int solve(State src) {
	queue<State> Q;
	src.dist = 0;
	Q.push(src);

	set<string> seen;
	seen.insert(src.encode());

	while (!Q.empty()) {
		State s = Q.front(); Q.pop();
		if (s.solved()) return s.dist;

		for (int dir = 0; dir < 4; dir++) {
			State t = s;
			if (!t.move(dir)) continue;

			string tenc = t.encode();
			if (seen.count(tenc) == 0) {
				seen.insert(tenc);
				Q.push(t);
			}
		}
	}

	return -1;
}

int main() {
	int M, W;
	for (int cs = 1; scanf("%d %d %d", &N, &M, &W) == 3 && N > 0; cs++) {
		State S;
		memset(&S, 0, sizeof(S));

		bool flag = true;

		for (int i = 1; i <= M; i++) {
			int row, col;
			scanf("%d %d", &row, &col);
			if (S.a[row][col] != 0) flag = false;
			S.a[row][col] = i;
		}

		for (int i = 1; i <= M; i++) {
			int row, col;
			scanf("%d %d", &row, &col);
			if (S.a[row][col] < 0) flag = false;
			if (S.a[row][col] > 0) {
				if (S.a[row][col] == i) {
					S.a[row][col] = 0;
					continue;
				}
				flag = false;
			}
			S.a[row][col] = -i;
		}

		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				for (int dir = 0; dir < 4; dir++) {
					int y1 = y + dy[dir];
					int x1 = x + dx[dir];
					may[y][x][dir] = valid(y1, x1) && valid(y, x);
				}
			}
		}

		for (int i = 0; i < W; i++) {
			int y1, x1, y2, x2;
			scanf("%d %d %d %d", &y1, &x1, &y2, &x2);

			for (int dir = 0; dir < 4; dir++) {
				if (y1 + dy[dir] == y2 && x1 + dx[dir] == x2)
					may[y1][x1][dir] = false;

				if (y2 + dy[dir] == y1 && x2 + dx[dir] == x1)
					may[y2][x2][dir] = false;
			}
		}

		int res = (flag ? solve(S) : -1);
		if (res < 0)
			printf("Case %d: impossible\n\n", cs);
		else
			printf("Case %d: %d moves\n\n", cs, res);
	}
}

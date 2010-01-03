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

int M, N, overhead;
int d[200][200];
vector<int> adj[400];
struct Segment { int x, y, h; } seg[200];

int main()
{
	int T;
	for (cin >> T; T--;) {
		cin >> M >> N >> overhead;
		for (int i = 0; i < N; i++) adj[i].clear();
		for (int i = 0; i < M; i++) {
			cin >> seg[i].x >> seg[i].y >> seg[i].h;
			--seg[i].x; --seg[i].y;
			adj[seg[i].x].push_back(i);
			adj[seg[i].y].push_back(i);
		}

		memset(d, 0x3f, sizeof(d));
		for (int i = 0; i < M; i++) d[i][i] = 0;

		for (int p = 0; p < N; p++) {
			for (int i = 0; i < adj[p].size(); i++) {
				for (int j = 0; j < adj[p].size(); j++) {
					int x = adj[p][i];
					int y = adj[p][j];
					d[x][y] = d[y][x] = min(d[x][y], abs(seg[x].h - seg[y].h) + overhead);
				}
			}
		}

		for (int k = 0; k < M; k++)
			for (int i = 0; i < M; i++)
				for (int j = 0; j < M; j++)
					d[i][j] <?= d[i][k] + d[k][j];

		int best = 1<<30;
		for (int i = 0; i < M; i++) {
			if (adj[seg[i].x].size() != 1 && adj[seg[i].y].size() != 1) continue;
			for (int j = i+1; j < M; j++) {
				if (adj[seg[j].x].size() != 1 && adj[seg[j].y].size() != 1) continue;
				best <?= d[i][j] + overhead;
			}
		}
		cout << best << '\n';
	}
}

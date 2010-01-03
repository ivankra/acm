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
#include <set>
using namespace std;
#define foreach(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

int height, width, P;
char maze[32][32];

struct Edge {
	int x, y, c;
};

int N, seen[2000];
vector<Edge> E;
vector<int> adj[10000];

int dfs(int x) {
	if (seen[x]) return 0;
	seen[x] = 1;
	if (x == 1) return 1;
	for (int i = 0; i < (int)adj[x].size(); i++) {
		int e = adj[x][i];
		if (E[e].c > 0 && dfs(E[e].y)) {
			--E[e].c;
			++E[e^1].c;
			return 1;
		}
	}
	return 0;
}

int Vin(int r, int c) { return 2+(r*width+c)*2; }
int Vout(int r, int c) { return 2+(r*width+c)*2+1; }

void add(int x, int y, int cap)
{
	Edge e;
	e.x = x; e.y = y; e.c = cap;
	adj[x].push_back(E.size());
	E.push_back(e);
	e.x = y; e.y = x; e.c = 0;
	adj[y].push_back(E.size());
	E.push_back(e);
}

int main()
{
	while (scanf("%d %d %d", &height, &width, &P) == 3) {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				scanf(" %c", &maze[i][j]);

		N = height * width * 2 + 10;
		E.clear();
		for (int i = 0; i < N; i++)
			adj[i].clear();

		for (int r = 0; r < height; r++) {
			for (int c = 0; c < width; c++) {
				for (int dir = 0; dir < 4; dir++) {
					int r1 = r + "0211"[dir] - '1';
					int c1 = c + "1102"[dir] - '1';
					if (r1 < 0 || r1 >= height || c1 < 0 || c1 >= width) continue;
					if (maze[r][c] == '~' || maze[r1][c1] == '~') continue;
					add(Vout(r, c), Vin(r1, c1), 1000000);
				}

				if (maze[r][c] == '~') {
					;
				} else if (maze[r][c] == '.') {
					add(Vin(r,c), Vout(r,c), 1);
				} else if (maze[r][c] == '*') {
					//add(Vin(r,c), Vout(r,c), 1);
					add(0, Vout(r, c), 1);
				} else if (maze[r][c] == '@') {
					add(Vin(r,c), Vout(r,c), 1000000);
				} else if (maze[r][c] == '#') {
					add(Vin(r,c), Vout(r,c), 1000000);
					add(Vout(r,c), 1, P);
				} else {
					abort();
				}
			}
		}

		int flow = 0;
		while (true) {
			memset(seen, 0, sizeof(seen));
			if (dfs(0)) flow++; else break;
		}
		printf("%d\n", flow);
	}
}

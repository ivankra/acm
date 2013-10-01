#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
using namespace std;

int N, P, gamesPlayed, gamesWon[64], gameV[64][64];
int seen[2000];
char table[64][64][2];

struct Edge { int x, y, cap; };
vector<Edge> E;
vector<int> adj[2000], inadj[2000];

bool cmp(int i, int j) { return gamesWon[i] < gamesWon[j]; }

void add(char s[2], char ch)
{
	for (int i = 0; i < 2; i++)
		if (s[i] == '-') { s[i] = ch; return ;}
}

void addEdge(int x, int y) {
	Edge e1 = { x, y, 1}, e2 = { y, x, 0 };
	adj[x].push_back(E.size());
	inadj[y].push_back(E.size());
	E.push_back(e1);

	adj[y].push_back(E.size());
	inadj[x].push_back(E.size());
	E.push_back(e2);
}

int dfs(int x) {
	if (x == 1) return 1;
	if (seen[x]++) return 0;
	for (int i = 0; i < (int)adj[x].size(); i++) {
		Edge &e = E[adj[x][i]];
		if (e.cap > 0 && dfs(e.y)) {
			e.cap--;
			E[adj[x][i]^1].cap++;
			return 1;
		}
	}
	return 0;
}

int aug(int pl) {
	memset(seen, 0, sizeof(seen));
	seen[0] = 1;
	if (!dfs(2+pl)) return 0;
	return 1;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		if (cs > 1) printf("\n");

		scanf("%d %d", &N, &P);
		P--;

		memset(gameV, 0xff, sizeof(gameV));
		for (int i = 0, k = 3+N; i < N; i++) {
			for (int j = i+1; j < N; j++) {
				gameV[i][j] = gameV[j][i] = k;
				k++;
			}
		}

		gamesPlayed = 0;
		memset(gamesWon, 0, sizeof(gamesWon));
		memset(table, 0xff, sizeof(table));

		E.clear();
		for (int i = 0; i < 2000; i++) {
			adj[i].clear();
			inadj[i].clear();
		}

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				for (int i = 0; i < 2; i++) {
					char ch;			//  here
					scanf(" %c", &ch);
					table[y][x][i] = ch;
					if (x <= y) continue;
					if (ch == '-') {
						addEdge(gameV[y][x], 1);
						addEdge(2+x, gameV[y][x]);
						addEdge(2+y, gameV[y][x]);
					} else {
						gamesPlayed++;
						if (ch == '0')
							gamesWon[x]++;
						else
							gamesWon[y]++;
					}
				}
			}
		}

		while (aug(P)) {
			gamesWon[P]++;
			gamesPlayed++;
		}

		while (gamesPlayed < N*(N-1)) {
			int i, v[100];
			for (i = 0; i < N; i++) v[i] = i;
			sort(v, v+N, cmp);

			for (i = 0; i < N; i++) {
				if (v[i] != P && aug(v[i])) break;
			}
			assert(i < N);
			gamesWon[v[i]]++;
			gamesPlayed++;
		}

		int m = 0;
		for (int x = 0; x < N; x++)
			if (x != P) m = max(m, gamesWon[x]);

		if (m > gamesWon[P]) {
			printf("Player %d can't win!\n", P+1);
		} else {
			printf("Player %d can win with %d point(s).\n\n", P+1, gamesWon[P] - m);

			for (int x = 0; x < N; x++) {
				for (int y = x+1; y < N; y++) {
					int v = gameV[x][y];
					for (int i = 0; i < (int)inadj[v].size(); i++) {
						Edge &e = E[inadj[v][i]];
						if (e.x == x+2 && e.cap == 0) {
							add(table[x][y], '1');
							add(table[y][x], '0');
						}
						if (e.x == y+2 && e.cap == 0) {
							add(table[y][x], '1');
							add(table[x][y], '0');
						}
					}
				}
			}

			for (int x = 0; x < N; x++) {
				for (int y = 0; y < N; y++)
					printf("%c%c ", table[x][y][0], table[x][y][1]);
				printf(": %d\n", gamesWon[x]);
			}
		}

	}
}

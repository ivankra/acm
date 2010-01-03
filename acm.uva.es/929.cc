#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

#define MAXCOST (2000*9+1)
#define INF 1000000

int N, M;
int maze[1024][1024];
int seen[1024*1024];

vector<int> Q[MAXCOST+100];

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf("%d", &maze[i][j]);
			}
		}

		for (int i = 0; i <= MAXCOST; i++)
			Q[i].clear();

		Q[0].push_back(0);

		for (int i = 0; i <= N*M; i++) seen[i] = INF;
		seen[0] = 0;

		for (int dist = 0; dist <= MAXCOST; dist++) {
			for (int i = 0; i < (int)Q[dist].size(); i++) {
				int t = Q[dist][i];
				if (seen[t] != dist) continue;

				for (int j = 0; j < 4; j++) {
					int y = t / M + "1102"[j] - '1';
					int x = t % M + "0211"[j] - '1';
					if (x < 0 || y < 0 || x >= M || y >= N) continue;

					int s = y * M + x;
					int d = dist + maze[y][x];
					if (seen[s] > d) {
						seen[s] = d;
						Q[d].push_back(s);
					}
				}
			}
		}

		printf("%d\n", seen[N*M-1] + maze[0][0]);
	}
}

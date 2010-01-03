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
#include <queue>
using namespace std;

char maze[32*32];
int N, h, H, s, S;
int dist[32*32][32*32], seen[32*32][32*32];
char prev[32*32][32*32];

int Dist(int a, int b) {
	int x = (a & 31) - (b & 31);
	int y = (a >> 5) - (b >> 5);
	return x*x + y*y;
}

int main()
{
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		memset(maze, '*', sizeof(maze));
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				int k = i * 32 + j;
				scanf(" %c", &maze[k]);
				char c = maze[k];
				if (c == 'H') H = k;
				if (c == 'h') h = k;
				if (c == 'S') S = k;
				if (c == 's') s = k;
			}
		}

		seen[H][h] = cs;
		dist[H][h] = Dist(H,h);

		priority_queue<pair<int, int> > Q;
		Q.push(make_pair(dist[H][h], H*1024+h));

		int delta[] = { -1, 1, 32, -32, 0 };
		char delta_c[] = "WESN ";

		while (!Q.empty()) {
			int jack = Q.top().second >> 10;
			int jill = Q.top().second & 1023;
			if (Q.top().first != dist[jack][jill]) { Q.pop(); continue; }
			Q.pop();
			if (jack == S && jill == s) break;

			for (int dir1 = 0; dir1 < 5; dir1++) {
				int ja = jack + delta[dir1];
				if ((dir1 == 4) ^ (maze[jack] == 'S')) continue;
				if (maze[ja] == '*' || maze[ja] == 's' || maze[ja] == 'h') continue;

				for (int dir2 = 0; dir2 < 5; dir2++) {
					int ji = jill + delta[dir2];
					if ((dir2 == 4) ^ (maze[jill] == 's')) continue;
					if (maze[ji] == '*' || maze[ji] == 'S' || maze[ji] == 'H') continue;

					if (seen[ja][ji] != cs) {
						seen[ja][ji] = cs;
						dist[ja][ji] = -1;
					}

					int d = min(dist[jack][jill], Dist(ja, ji));
					if (d > dist[ja][ji]) {
						dist[ja][ji] = d;
						prev[ja][ji] = dir1 * 8 + dir2;
						Q.push(make_pair(d, ja*1024+ji));
					}
				}
			}
		}

		if (cs != 1) printf("\n");
		printf("%.2lf\n", sqrt(dist[S][s]+0.0));

		string str[2];
		int jack = S, jill = s;
		assert(seen[jack][jill] == cs);
		while (jack != H || jill != h) {
			int dir1 = prev[jack][jill] / 8;
			int dir2 = prev[jack][jill] % 8;
			if (dir1 < 4) str[0] += delta_c[dir1];
			if (dir2 < 4) str[1] += delta_c[dir2];
			jack -= delta[dir1];
			jill -= delta[dir2];
		}
		reverse(str[0].begin(), str[0].end());
		reverse(str[1].begin(), str[1].end());
		printf("%s\n", str[0].c_str());
		printf("%s\n", str[1].c_str());
	}
}

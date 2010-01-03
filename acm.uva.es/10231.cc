#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

#define INF 0x3fffffff

struct State {
	int y, x, c;
	State(int Y, int X, int C=0) : y(Y), x(X), c(C) {}
};

int best_n, best_tm, nrows, ncols, machdist[32][32], dist[32][32][1024];
int seen[32][32][1024], seen_id, nbits[1024], tr_id[32][32], n_tr;
char Map[32][32];

void do_find() {
	queue<State> Q;

	best_n = best_tm = 0;
	seen_id++;

	n_tr = 0;
	memset(tr_id, 0xff, sizeof(tr_id));

	for (int i = 1; i <= nrows; i++) {
		for (int j = 1; j <= ncols; j++) {
			if (Map[i][j] == 'O') {
				Q.push(State(i, j, 0));
				seen[i][j][0] = seen_id;
				dist[i][j][0] = 0;
			}
			if (Map[i][j] == '*')
				tr_id[i][j] = n_tr++;
		}
	}

	while (!Q.empty()) {
		State s = Q.front(); Q.pop();
		int d = dist[s.y][s.x][s.c];

		if (machdist[s.y][s.x] <= d) continue;

		if (nbits[s.c] > best_n ||
		    (nbits[s.c] == best_n && d < best_tm)) {
			best_n = nbits[s.c];
			best_tm = d;
		}

		// movements
		for (int dir = 0; dir < 4; dir++) {
			State ss(s.y + "0211"[dir] - '1',
			         s.x + "1102"[dir] - '1',
			         s.c);
			if (Map[ss.y][ss.x] == '#') continue;
			if (machdist[ss.y][ss.x] <= d+1) continue;
			if (seen[ss.y][ss.x][ss.c] != seen_id) {
				seen[ss.y][ss.x][ss.c] = seen_id;
				dist[ss.y][ss.x][ss.c] = d + 1;
				Q.push(ss);
			}
		}

		// picking
		if (Map[s.y][s.x] == '*' && machdist[s.y][s.x] > d+1) {
			State ss(s.y, s.x, s.c | (1 << tr_id[s.y][s.x]));
			if (seen[ss.y][ss.x][ss.c] != seen_id) {
				seen[ss.y][ss.x][ss.c] = seen_id;
				dist[ss.y][ss.x][ss.c] = d + 1;
				Q.push(ss);
			}
		}
	}
}

void do_mach() {
	queue<State> Q;

	for (int i = 0; i <= nrows+1; i++) {
		for (int j = 0; j <= ncols+1; j++) {
			machdist[i][j] = INF;
			if (Map[i][j] == 'X') {
				machdist[i][j] = 0;
				Q.push(State(i,j));
			}
		}
	}

	while (!Q.empty()) {
		State p = Q.front(); Q.pop();

		for (int d = 0; d < 4; d++) {
			State q(p.y + "0211"[d] - '1',
			        p.x + "1102"[d] - '1');
			if (Map[q.y][q.x] != '#' && machdist[q.y][q.x] == INF) {
				machdist[q.y][q.x] = machdist[p.y][p.x] + 1;
				Q.push(q);
			}
		}
	}
}

int main() {
	memset(seen, 0, sizeof(seen));
	seen_id = 42;

	nbits[0] = 0;
	for (int i = 1; i < 1024; i++) nbits[i] = 1 + nbits[i & (i-1)];

	for (int cs = 1; scanf("%d %d", &nrows, &ncols) == 2; cs++) {
		memset(Map, '#', sizeof(Map));
		for (int i = 1; i <= nrows; i++) {
			for (int j = 1; j <= ncols; j++) {
				int c;
				while ((c = getchar()) != EOF)
					if (strchr("*.#XO", c) != NULL) break;
				Map[i][j] = c;
			}
		}

		do_mach();
		do_find();

		printf("Case %d:\n", cs);
		if (best_n == 0) {
			printf("No treasures can be collected.\n\n");
		} else {
			printf("Maximum number of collectible treasures: %d.\n", best_n);
			printf("Minimum Time: %d sec.\n\n", best_tm);
		}
	}
}

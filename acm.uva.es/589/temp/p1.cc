#include <cstdio>
#include <cctype>
#include <vector>
using namespace std;

int dx[]={1,-1,0,0}, dy[]={0,0,1,-1}; char ds[]="ewsn";
int seen[512*512], prev[512*512], prevc[512*512];
int wall[32][32], cell[32][32], cell_y[512], cell_x[512], R, C, cs;
int start_cell, goal_cell, box_cell;

int solve() {
	for(int i=0;i<32;i++) for(int j=0;j<32;j++) wall[i][j]=1;

	for (int i = 1, k = 0; i <= R; i++) {
		for (int j = 1, c; j <= C; j++) {
			cell_y[k] = i; cell_x[k] = j; cell[i][j] = k++;
			while ((c = getchar()) != EOF)
				if (strchr("#.SBT", c) != NULL) break;
			wall[i][j] = (c == '#');
			if (c == 'S')
				start_cell = cell[i][j];
			else if (c == 'B')
				box_cell = cell[i][j];
			else if (c == 'T')
				goal_cell = cell[i][j];
		}
	}

	vector<int> Q1, Q2, Q3;
	int start = (start_cell << 9) | box_cell;
	seen[start] = cs;
	Q1.push_back(start);

	int fin = -1;
	for (;;) {
		if (Q1.empty()) {
			if (!Q2.empty()) Q1.swap(Q2);
			else if (!Q3.empty()) Q1.swap(Q3);
			else return 0;
		}

		int s = Q1.back();
		Q1.pop_back();

		int man = (s >> 9), box = (s & 511);
		if (box == goal_cell) { fin = s; goto ok; }

		for (int d = 0; d < 4; d++) {
			int y = cell_y[man] + dy[d], x = cell_x[man] + dx[d];
			int c = cell[y][x];
			if (wall[y][x]) continue;

			if (c != box) {
				int t = (c << 9) | box;
				if (seen[t] == cs) continue;
				seen[t] = cs;
				prev[t] = s;
				prevc[t] = ds[d];
				Q2.push_back(t);
				continue;
			}

			int y1 = y + dy[d], x1 = x + dx[d], c1 = cell[y1][x1];
			if (wall[y1][x1]) continue;

			int t = (c << 9) | c1;
			if (seen[t] == cs) continue;
			seen[t] = cs;
			prev[t] = s;
			prevc[t] = toupper(ds[d]);
			if (c1 == goal_cell) { fin = t; goto ok; }
			Q3.push_back(t);
		}
	}

ok:	vector<char> path;
	for (int x = fin; x != start; x = prev[x])
		path.push_back(prevc[x]);
	for (; path.size() > 0; path.pop_back())
		putchar(path.back());
	printf("\n\n");	

	return 1;
}

int main()
{
	memset(seen, 0, sizeof(seen));
	for (cs = 1; scanf("%d %d", &R, &C) == 2; cs++) {
		if (R == 0 && C == 0) break;
		printf("Maze #%d\n", cs);
		if (!solve()) printf("Impossible.\n\n");
	}
}

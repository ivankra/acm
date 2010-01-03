#include <cstdio>
#include <cstring>

int m, n;
char maze[64][64], fix[64][64];

int rec(int y, int x, int dy, int dx) {
	while (maze[y+dy][x+dx] == '.') y += dy, x += dx;
	if (maze[y+dy][x+dx] == '*') return 0;
	if (maze[y+dy][x+dx] == 't') return 1;
	if (maze[y+dy][x+dx] == 's') return 0;

	if (fix[y+dy][x+dx] == 0) {
		fix[y+dy][x+dx] = 1;
		if (rec(y,x,dy,dx)) return 1;
		maze[y+dy][x+dx] = (maze[y+dy][x+dx] == '/' ? '\\' : '/');
		if (rec(y,x,dy,dx)) return 1;
		fix[y+dy][x+dx] = 0;
		return 0;
	}

	if ((maze[y+dy][x+dx]=='/') ^ (dy == 0))
		return rec(y+dy, x+dx, dx, -dy);
	else
		return rec(y+dy, x+dx, -dx, dy);
}

int main() {
	for (int cs = 1; scanf("%d %d", &m, &n) && m > 0 && n > 0; cs++) {
		memset(maze, '*', sizeof(maze));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf(" %c", &maze[i][j]);

		memset(fix, 0, sizeof(fix));
		for (int y = 1, k = 0; y <= n; y++) {
			for (int x = 1; x <= m; x++) {
				if (maze[y][x] != '.') continue;
				if (y==1 || y==n || x==1 || x==m)
					maze[y][x] = "st"[k++];
			}
		}

		for (int y = 1; y <= n; y++) {
			for (int x = 1; x <= m; x++) {
				if (maze[y][x] != 's') continue;
				if (y == 1) rec(y,x, 1,0);
				else if (y == n) rec(y,x, -1,0);
				else if (x == 1) rec(y,x, 0,1);
				else if (x == m) rec(y,x, 0,-1);
			}
		}

		if (cs > 1) printf("\n");
		for (int y = 1; y <= n; y++) {
			for (int x = 1; x <= m; x++)
				if (maze[y][x]=='s' || maze[y][x]=='t')
					maze[y][x] = '.';
			printf("%.*s\n", m, maze[y]+1);
		}
	}
}

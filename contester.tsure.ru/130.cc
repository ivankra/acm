#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

#define INF (1<<30)

struct State { int x, y, r; } S,T;
int dx[]={1,-1,0,0}, dy[]={0,0,1,-1}, map[64][64], dist[64][64][4], n;

int in(const State &a) {
	return (1<=a.x&&a.x<=n && 1<=a.y&&a.y<=n) || (a.x==T.x&&a.y==T.y);
}

int main()
{
	int m, x0, y0, x1, y1;
	scanf("%d %d %d %d %d %d %d", &n, &S.r, &S.x, &S.y, &T.x, &T.y, &m);
	memset(map, 0, sizeof(map));
	while (m-- > 0 && scanf("%d %d %d %d", &x0, &y0, &x1, &y1) == 4) {
		for (int d = 0; d < 4; d++) {
			if (x0+dx[d]==x1 && y0+dy[d]==y1) map[x0][y0] |= 1<<d;
			if (x1+dx[d]==x0 && y1+dy[d]==y0) map[x1][y1] |= 1<<d;
		}
	}
	for(int x=0;x<64;x++) for(int y=0;y<64;y++) for(int d=0;d<4;d++)
		dist[x][y][d] = INF;
	dist[S.x][S.y][S.r] = 0;

	queue<State> Q;
	for (Q.push(S); !Q.empty();) {
		State a = Q.front(); Q.pop();
		for (int d = 0; d < 4; d++) {
			State b = {a.x+dx[d], a.y+dy[d], a.r };
			if (!in(b)) continue;

			if (map[a.x][a.y] & (1 << d)) {
				if (a.r == 0) continue;
				b.r = a.r - 1;
			}

			int bd = dist[a.x][a.y][a.r]+1;
			if (dist[b.x][b.y][b.r] <= bd) continue;
			dist[b.x][b.y][b.r] = bd;
			Q.push(b);
		}
	}

	int best = INF;
	for (int r = 0; r < S.r; r++)
		best <?= dist[T.x][T.y][r];

	for (int r = S.r; r >= 0; r--)
		if (dist[T.x][T.y][r] == best && best < INF) {
			printf("%d %d\n", best, S.r-r);
			return 0;
		}
	printf("0 0\n");
}

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <deque>
#include <algorithm>
using namespace std;
typedef pair<int,int> P;
typedef struct { int y,x,z[4]; } state;
#define INF 0x3FFFFFFF

int dy[]={-1,0,1,0}, dx[]={0,1,0,-1}, C;
int map[32][32], dist[32][32], n, lim, next;

int seen[32][32], id=42;
unsigned short xseen[21][21][14461];

int go(state s)
{
	int i, j, k;

#define Y(d) (C+((((d&1)?s.x:s.y)-C) * (((d&1)^(d>>1))?-1:1)))
#define X(d) (C+((((d&1)?s.y:s.x)-C) * ((d&2)?-1:1)))

	for (k = i = 0; i < 4; i++) k = max(k, s.z[i] + dist[Y(i)][X(i)]);
	if (k > lim) { next = min(next, k); return 0; }

	if (s.x<1 || s.y<1 || s.x>n || s.y>n) return 1;

	i = s.z[0]*1000+s.z[1]*100+s.z[2]*10+s.z[3];
	if (xseen[s.y-1][s.x-1][i] == id) return 0;
	xseen[s.y-1][s.x-1][i] = id;

	for (i = 0; i < 4; i++) {
		if (seen[s.y+dy[i]][s.x+dx[i]]) continue;
		s.y += dy[i]; s.x += dx[i];
		for (j = 0; j < 4; j++) if (map[Y(j)][X(j)]=='R') s.z[j]++;
		seen[s.y][s.x]=1;
		if (go(s)) return 1;
		seen[s.y][s.x]=0;
		for (j = 0; j < 4; j++) if (map[Y(j)][X(j)]=='R') s.z[j]--;
		s.y -= dy[i]; s.x -= dx[i];
	}

	return 0;
}

void prep()
{
	deque<P> q, r;
	int i, j;

	for (i = 0; i <= n+1; i++) for (j = 0; j <= n+1; j++) dist[i][j] = INF;
	for (i = 0; i <= n+1; i++)
		dist[i][0] = dist[i][n+1] = dist[0][i] = dist[n+1][i] = 0;

	for (i = 0; i <= n+1; i++)
		for (j = 0; j <= n+1; j++)
			if (dist[i][j] == 0) q.push_back(P(i,j));

	while (!q.empty()) {
		P a = q.front(); q.pop_front();
		for (i = 0; i < 4; i++) {
			int y=a.first+dy[i], x=a.second+dx[i];
			if (y<0 || x<0 || y>n || x>n || dist[y][x]<INF) continue;
			dist[y][x] = dist[a.first][a.second] + (map[y][x]=='R'?1:0);
			if (map[y][x] != 'R') q.push_back(P(y,x));
			else r.push_back(P(y,x));
		}
		if (q.empty()) q.swap(r);
	}

	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			if (map[i][j]=='R') dist[i][j]--;
}

int main()
{
	int i, j, k;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < 32; i++)
			for (j = 0; j < 32; j++) map[i][j] = '.';

		for (i = 1; i <= n; i++)
			for (j = 1; j <= n && (k = getchar()) != EOF;)
				if (k=='R' || k=='P' || k=='.') map[i][j++] = k;

		C = (n + 1) / 2;

		prep();

		for (lim = 0;; lim = next) {
			next = INF;
			memset(seen,0,sizeof(seen));
			if (++id > 65530) { memset(xseen,0,sizeof(xseen)); id=1; }
			state s={C,C,{0,0,0,0}};
			if (go(s)) break;
		}

		printf("At most %d rose(s) trampled.\n", lim);
	}

	return 0;
}

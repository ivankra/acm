#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char map[1024][1024];
int rows, cols, ty, tx, qh, qt, dy[]={1,-1,0,0}, dx[]={0,0,1,-1};

int qy[1048576], qx[1048576];
int dist[1048576];

int solve()
{
	int i;

	if (ty==qy[0] && tx==qx[0]) return 0;

	map[qy[0]][qx[0]] = 1; dist[0]=0;
	for (qh = 0, qt = 1; qh < qt; qh++) {
		for (i = 0; i < 4; i++) {
			int y = qy[qh]+dy[i], x = qx[qh]+dx[i];
			if (map[y][x]==0) {
				if (y==ty && x==tx) return dist[qh]+1;
				map[y][x] = 1;
				qy[qt]=y; qx[qt]=x; dist[qt++]=dist[qh]+1;
			}
		}
	}

assert(1==0);
	return -1;
}

int main()
{
	int i, j, m, r, q, cl;

	while (scanf("%d %d", &rows, &cols) == 2 && rows > 0) {
		for (i = 1; i <= rows; i++)
			for (j = 1; j <= cols; j++) map[i][j]=0;
		for (i = 0; i <= rows+1; i++) map[i][0]=map[i][cols+1]=1;
		for (i = 0; i <= cols+1; i++) map[0][i]=map[rows+1][i]=1;

		for (scanf("%d", &m); m-- > 0 && scanf("%d %d", &r, &q) == 2;)
			while (q-->0 && scanf("%d",&cl)==1) map[r+1][cl+1]=1;

		scanf("%d %d", &qy[0], &qx[0]); qy[0]++; qx[0]++;
		scanf("%d %d", &ty, &tx); ty++; tx++;

		assert(map[ty][tx]==0);

		printf("%d\n", solve());
	}

	return 0;
}

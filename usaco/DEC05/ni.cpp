/*
TASK: ni
ID: infnty1
LANG: C++
*/
/* Algorithm: BFS from Bessie's starting location and Knights' location. */   
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INF 0x3FFFFFFF

char map[1024][1024];
int dist1[1024][1024], dist2[1024][1024];
int queue[1048576], head, tail, W,H, by,bx, ky,kx;
int dx[] = {1,-1,0,0}, dy[] = {0,0,1,-1};

/* dist1[y][x] = distance from Bessie
   dist2[y][x] = distance from Knights */

int main()
{
	int i, j, k;

	freopen("ni.in", "r", stdin);
	freopen("ni.out", "w", stdout);

	scanf("%d %d", &W, &H);
	assert(1<=W&&W<=1000 && 1<=H&&H<=1000);

	for (i = 0; i <= H+1; i++) map[i][0] = map[i][W+1] = 1;
	for (j = 0; j <= W+1; j++) map[0][j] = map[H+1][j] = 1;

	for (i = 1; i <= H; i++)
		for (j = 1; j <= W; j++) {
			int x;
			scanf("%d", &x);
			map[i][j] = x;
			if (x == 2) { by=i; bx=j; map[i][j]=0; }
			else if (x == 3) { ky=i; kx=j; map[i][j]=1; }
		}

	for (i = 1; i <= H; i++) for (j = 1; j <= W; j++) dist1[i][j]=INF;
	queue[0] = (by << 10) | bx; dist1[by][bx]=0;
	for (head=0, tail=1; head < tail; head++) {
		int y = queue[head] >> 10, x = queue[head] & 1023;
		for (i = 0; i < 4; i++) {
			int y1 = y + dy[i], x1 = x + dx[i];
			if (map[y1][x1] & 1) continue;
			if (dist1[y1][x1] != INF) continue;
			dist1[y1][x1] = dist1[y][x] + 1;
			queue[tail++] = (y1 << 10) | x1;
		}
	}

	for (i = 1; i <= H; i++) for (j = 1; j <= W; j++) dist2[i][j]=INF;
	queue[0] = (ky << 10) | kx; dist2[ky][kx]=0;
	for (head=0, tail=1; head < tail; head++) {
		int y = queue[head] >> 10, x = queue[head] & 1023;
		for (i = 0; i < 4; i++) {
			int y1 = y + dy[i], x1 = x + dx[i];
			if (map[y1][x1] & 1) continue;
			if (dist2[y1][x1] != INF) continue;
			dist2[y1][x1] = dist2[y][x] + 1;
			queue[tail++] = (y1 << 10) | x1;
		}
	}

	for (k = INF, i = 1; i <= H; i++)
		for (j = 1; j <= W; j++)
			if (map[i][j]==4 && dist1[i][j]+dist2[i][j]<k)
				k = dist1[i][j] + dist2[i][j];

	printf("%d\n", k);

	return 0;
}

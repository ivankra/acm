/*
ID: infnty1
PROB: maze1
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define INF 0x3FFFFFFF

struct loc { int y, x; loc(int _y, int _x){y=_y;x=_x;} };
int w, h, U[128][128], L[128][128], D[128][128];
int dx[]={1,-1,0,0}, dy[]={0,0,1,-1};

int main()
{
	char s[1024];

	freopen("maze1.in", "r", stdin);
	freopen("maze1.out", "w", stdout);

	gets(s);
	sscanf(s, "%d %d", &w, &h);

	memset(U, 0, sizeof(U));
	memset(L, 0, sizeof(L));
	memset(D, 0, sizeof(D));

	for (int r = 1; ; r++) {
		gets(s);
		for (int c = 1; c <= w; c++)
			if (s[2*c-1]==' ') U[r][c]=1;

		if (r > h) break;

		gets(s);
		for (int c = 1; c <= w+1; c++)
			if (s[2*c-2]==' ') L[r][c]=1;
	}

/*	for (int y = 0; y <= h+1; y++) {
		for (int x = 0; x <= w+1; x++)
			printf("%c%c ",U[y][x]?'U':'.',L[y][x]?'L':'.');			
		printf("\n");
	}
*/

	for (int r=1; r<=h; r++) for (int c=1; c<=w; c++) D[r][c] = INF;

	queue<loc> q;

	for (int i = 1; i <= h; i++) {
		q.push(loc(i,0));
		q.push(loc(i,w+1));
	}

	for (int i = 1; i <= w; i++) {
		q.push(loc(0,i));
		q.push(loc(h+1,i));
	}

	for (; !q.empty(); q.pop()) {
		int y=q.front().y, x=q.front().x;

		if (U[y][x] && D[y-1][x]==INF) {
			D[y-1][x] = D[y][x] + 1;
			q.push(loc(y-1,x));
		}

		if (L[y][x] && D[y][x-1]==INF) {
			D[y][x-1] = D[y][x] + 1;
			q.push(loc(y,x-1));
		}

		if (U[y+1][x] && D[y+1][x]==INF) {
			D[y+1][x] = D[y][x] + 1;
			q.push(loc(y+1,x));
		}

		if (L[y][x+1] && D[y][x+1]==INF) {
			D[y][x+1] = D[y][x] + 1;
			q.push(loc(y,x+1));
		}
	}

	int r = 0;
	for (int y = 1; y <= h; y++)
		for (int x = 1; x <= w; x++)
			if (D[y][x] < INF) r = max(r, D[y][x]);
	printf("%d\n", r);

	return 0;
}

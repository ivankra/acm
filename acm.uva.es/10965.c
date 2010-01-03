#include <stdio.h>
#include <string.h>
#include <assert.h>

int A[128][128], n, m, k, T1, T2;
struct { int y, x, p, r; char d; } z[1024];

int dx[] = { 0, 1, 0, -1 }, dy[] = { -1, 0, 1, 0 };
char ds[] = "NESW";

int valid(int y, int x) { return (1<=y&&y<=n && 1<=x&&x<=m); }
void mark(int y, int x) { if (valid(y,x)) A[y][x]=1; }

void go(int w)
{
	int d, d0, i, j, t, p=z[w].p;

	if (z[w].r > 100) z[w].r=100;

	mark(z[w].y, z[w].x);
	d0 = strchr(ds, z[w].d & ~0x20) - ds;

	for (i = 0, t = T1; i < 4 && t <= T2;) {
		j = t % (4*p+4);
		if (j == (p+1)-1 || j == 2*(p+1)-1 || j == 3*(p+1)-1 || j == 4*(p+1)-1) {
			t++;
			continue;
		}

		d = (d0 + j / (p+1)) % 4;
		for (j = 0; j <= z[w].r; j++)
			mark(z[w].y+dy[d]*j, z[w].x+dx[d]*j);

		for (j = 1; j < 4; j++)
			if ((t % (4*p+4)) < j*(p+1)-1) break;
		t += j*(p+1)-1 - (t % (4*p+4));
		i++;
	}
}

int main()
{
	int i, j;

	while (scanf("%d %d %d", &n, &m, &k) == 3 && n > 0) {
		for (i = 0; i < k; i++)
			scanf("%d %d %d %d %c", &z[i].y, &z[i].x, &z[i].p, &z[i].r, &z[i].d);

		memset(A, 0, sizeof(A));
		scanf("%d %d", &T1, &T2);

		for(i=0;i<k;i++) go(i);
		for(k=0,i=1;i<=n;i++) for(j=1;j<=m;j++) k+=1-A[i][j];

		printf("%d\n", k);
	}

	return 0;
}

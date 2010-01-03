/*
ID: infnty1
PROB: castle
LANG: C
*/
#include <stdio.h>
#include <string.h>

int w[64][64], rid[64][64], rsize[64*64], m, n, NR;

int max(int x, int y) { return x>y?x:y;}

int dfs()
{
	int dx[]={-1,0,1,0}, dy[]={0,-1,0,1}, df[]={1,2,4,8};
	int v[64][64], x, y, x0, y0, r, Y[64*64], X[64*64], d, t, s;

	memset(v, 0, sizeof(v));
	NR=0;
	for (r = 1, y0 = 0; y0 < n; y0++) for(x0=0;x0<m;x0++) {
		if (v[y0][x0]) continue;
		NR++; v[Y[0]=y0][X[0]=x0]=1; s=1;
		for (t=1; t-->0;) {
			x=X[t]; y=Y[t];
			rid[y][x]=NR;
			for(d=0;d<4;d++) {
				if ((w[y][x] & df[d]) != 0 || v[y+dy[d]][x+dx[d]]) continue;
				v[Y[t]=y+dy[d]][X[t]=x+dx[d]]=1; t++; s++;
			}
		}
		rsize[NR]=s;
		r=max(r,s);
	}

	return r;
}

int main()
{
	int i, j, k;

	freopen("castle.in", "r", stdin);
	freopen("castle.out", "w", stdout);

	scanf("%d %d", &m, &n);
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) scanf("%d", &w[i][j]);

	i = k = dfs();
	printf("%d\n%d\n", NR, i);

	for (i = n-1; i >= 0; i--)
		for (j = 0; j < m; j++) {
			if (i>0 && (w[i][j]&2)==2 && rid[i][j]!=rid[i-1][j])
				k = max(k,rsize[rid[i][j]]+rsize[rid[i-1][j]]);
			if (j<m-1 && (w[i][j]&4)==4 && rid[i][j]!=rid[i][j+1])
				k = max(k,rsize[rid[i][j]]+rsize[rid[i][j+1]]);
		}
	printf("%d\n",k);

	for (j = 0; j < m; j++) {
		for (i = n-1; i >= 0; i--) {
			if (i>0 && (w[i][j]&2)==2 && rid[i][j]!=rid[i-1][j] &&
			    k==rsize[rid[i][j]]+rsize[rid[i-1][j]]) {
				printf("%d %d N\n",i+1,j+1); return 0;
			}
			if (j<m-1 && (w[i][j]&4)==4 && rid[i][j]!=rid[i][j+1] &&
			    k == rsize[rid[i][j]]+rsize[rid[i][j+1]]) {
				printf("%d %d E\n",i+1,j+1); return 0;
			}
		}
	}

	return 0;
}

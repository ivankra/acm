#include <stdio.h>
#include <string.h>
#include <assert.h>

#define INF	0x3FFFFFFF
#define N	8192
#define K	1024

int next[2*N], adj[2*N], vant[N], ant[K], chase[K], n, k, id;
int Tgot[N], Tdist[N], Tant[N], Tmoved[N];

void ch(int p, int x, int tm)
{
	int i;

/*printf("ch(p=%d, x=%d, tm=%d)  Tdist[x]=%d Tant[x]=%d\n",p,x,tm,Tdist[x],Tant[x]);*/

	if (Tdist[x] == INF || tm == 0) return;
	
	if (x == ant[Tant[x]])
		return;

	if (!Tmoved[Tant[x]] && Tdist[x] <= tm) {
/*printf("ant %d: %d -> %d\n", Tant[x], ant[Tant[x]], x);*/

		vant[ant[Tant[x]]] = 0;
		Tdist[ant[Tant[x]]] = INF;
		vant[x] = Tant[x];
		ant[Tant[x]] = x;
		Tmoved[Tant[x]] = 1;
		tm = Tdist[x];
	} else if (Tmoved[Tant[x]] && Tdist[x] < tm) {
		tm = Tdist[x];
	}

	for (i = next[x]; i != 0; i = next[i])
		if (adj[i] != p) ch(x, adj[i], tm);
}

void go(int p, int x)
{
	int i, y;

	if (vant[x] > 0) {
		Tdist[x] = 0;
		Tant[x] = vant[x];
		return;
	}
	
	Tdist[x] = INF;
	Tant[x] = 0;

	for (i = next[x]; i != 0; i = next[i]) {
		y = adj[i];
		if (y == p) continue;

		go(x, y);
		if ((Tdist[y] + 1) < Tdist[x] ||
		    ((Tdist[y] + 1) == Tdist[x] && Tant[y] < Tant[x])) {
			Tdist[x] = Tdist[y] + 1;
			Tant[x] = Tant[y];
		}
	}
}

int main()
{
	int i, x, y, z;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i <= n; i++) next[i] = 0;
		for (z = n+1, i = 1; i < n && scanf("%d %d", &x, &y) == 2; i++) {
			adj[z] = y; next[z] = next[x]; next[x] = z++;
			adj[z] = x; next[z] = next[y]; next[y] = z++;
		}

		for (i = 0; i <= n; i++) vant[i] = 0;

		scanf("%d", &k);
		for (i = 1; i <= k; i++) {
			chase[i] = 0;
			scanf("%d", &ant[i]);
			vant[ant[i]] = i;
		}

/*printf("ants:");for(i=1;i<=k;i++)printf(" %d",ant[i]);printf("\n");*/

		for (scanf("%d", &y); y-- > 0 && scanf("%d", &x) == 1;) {
			for (i = 0; i <= n; i++) Tdist[i] = INF;
			for (i = 0; i <= n; i++) Tmoved[i] = 0;

/*printf("x=%d\n",x);*/
			go(0, x);
			ch(0, x, INF-1);
			chase[vant[x]]++;
/*printf("chased: %d\n\n", vant[x]);
printf("ants:");for(i=1;i<=k;i++)printf(" %d",ant[i]);printf("\n");*/
		}

		for (i = 1; i <= k; i++)
			printf("%d %d\n", ant[i], chase[i]);
	}

	return 0;
}


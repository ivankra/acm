#include <stdio.h>

#define INF	0x3FFFFFFF
#define N	5120
#define K	1024

static int next[3*N], adj[3*N], vant[N], ant[K], chase[K], n, k, id=42;
static int Tgot[N], Tdist[N], Tant[N], Tmoved[N];

static void ch(int p, int x, int tm)
{
	int i;

	if (Tgot[x] != id || x == ant[Tant[x]]) return;
	
	if (Tdist[x] <= tm) {
		tm = Tdist[x];
		if (Tmoved[Tant[x]] != id) {
			vant[ant[Tant[x]]] = 0;
			Tgot[ant[Tant[x]]] = 0;
			vant[x] = Tant[x];
			ant[Tant[x]] = x;
			Tmoved[Tant[x]] = id;
		}
		if (tm == 0) return;
	}

	for (i = next[x]; i != 0; i = next[i])
		if (adj[i] != p) ch(x, adj[i], tm);
}

static void go(int p, int x)
{
	int i, y;

	if (vant[x] > 0) {
		Tdist[x] = 0;
		Tgot[x] = id;
		Tant[x] = vant[x];
		return;
	}

	Tdist[x] = INF;
	Tgot[x] = 0;
	Tant[x] = 0;

	for (i = next[x]; i != 0; i = next[i]) {
		y = adj[i];
		if (y == p) continue;

		go(x, y);
		if ((Tdist[y] + 1) < Tdist[x] ||
		    ((Tdist[y] + 1) == Tdist[x] && Tant[y] < Tant[x])) {
			Tdist[x] = Tdist[y] + 1;
			Tgot[x] = id;
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

		for (scanf("%d", &y); y-- > 0 && scanf("%d", &x) == 1;) {
			id++;
			go(0, x);
			ch(0, x, INF-1);
			chase[vant[x]]++;
		}

		for (i = 1; i <= k; i++)
			printf("%d %d\n", ant[i], chase[i]);
	}

	return 0;
}


#include <stdio.h>
#include <string.h>

#define	SOURCE	0
#define	SINK	1
#define	MAXV	2048
#define	MAXC	131072

int n, m, nvert, vfinal[32];
int adj[MAXV], ref[MAXC], rev[MAXC], next[MAXC], cap[MAXC], last;
struct { int a[32], vin[32], vout[32], vmid1[32], vmid2[32]; } c[32];

int find()
{
	static int p[MAXV], s[MAXV];
	int i, j, t;

	for (i = 0; i < nvert; i++)
		p[i] = 0;

	for (p[s[0] = SOURCE] = -1, t = 1; t-- > 0;)
		for (j = adj[i = s[t]]; j != 0; j = next[j])
			if (cap[j] > 0 && p[ref[j]] == 0)
				p[s[t++] = ref[j]] = j;

	if (p[SINK] == 0)
		return 0;

	for (i = SINK; i != SOURCE; i = ref[rev[p[i]]]) {
		cap[p[i]]--;
		cap[rev[p[i]]]++;
	}

	return 1;
}

void add(int u, int v, int c)
{
	int t, s;

	t = ++last;
	s = ++last;

	ref[t] = v;
	next[t] = adj[u];
	adj[u] = t;
	cap[t] = c;
	rev[t] = s;

	ref[s] = u;
	next[s] = adj[v];
	adj[v] = s;
	cap[s] = 0;
	rev[s] = t;
}

int solve()
{
	int i, j, k, t, u;

	scanf("%d %d", &n, &m);

	memset(c, 0, sizeof(c));
	memset(adj, 0, sizeof(adj));
	last = 0;

	for (i = 0; i < n && scanf("%d", &t) == 1; i++)
		while (t-- > 0 && scanf("%d", &u) == 1)
			c[i].a[u - 1]++;

	nvert = 2;
	for (i = 0; i < m; i++)
		add(vfinal[i] = nvert++, SINK, 1);

	for (i = 0; i < m; i++)
		if (c[0].a[i] > 0) {
			if (c[0].a[i] > 1)
				add(SOURCE, c[0].vout[i] = nvert++, c[0].a[i] - 1);
			add(SOURCE, vfinal[i], 1);
		}
	
	for (i = 1; i < n; i++) {
		for (j = 0; j < m; j++)
			if (c[i].a[j] == 0) {
				c[i].vin[j] = nvert++;
				c[i].vmid1[j] = nvert++;
				add(c[i].vin[j], c[i].vmid1[j], 1);
			}

		for (j = 0; j < m; j++)
			if (c[i].a[j] > 1) {
				c[i].vmid2[j] = nvert++;
				c[i].vout[j] = nvert++;
				add(c[i].vmid2[j], c[i].vout[j], c[i].a[j] - 1);
				add(c[i].vout[j], vfinal[j], 1);
			}

		for (j = 0; j < m; j++) {
			if (c[i].vmid1[j] == 0) continue;
			for (k = 0; k < m; k++)
				if (c[i].vmid2[k] != 0)
					add(c[i].vmid1[j], c[i].vmid2[k], 1);
		}
	}

	for (i = 0; i < n; i++)
		for (j = 1; j < n; j++)
			for (k = 0; k < m; k++)
				if (c[i].vout[k] != 0 && c[j].vin[k] != 0)
					add(c[i].vout[k], c[j].vin[k], 1);

	for (t = 0; find(); t++);
	return t;
}

int main()
{
	int c, t;
	
	for (scanf("%d", &t), c = 1; c <= t; c++)
		printf("Case #%d: %d\n", c, solve());

	return 0;
}

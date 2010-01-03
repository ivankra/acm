#include <stdio.h>
#include <string.h>

#define MAXM	131072
#define SOURCE	0
#define SINK	1
#define SUBJ(s)	(2 + (s))
#define PROB(p) (2 + nsubj + (p))

int adj[1024], ref[MAXM], rev[MAXM], next[MAXM], cap[MAXM], freelist;
int subjc[32], nsubj, nprob, nvert;

void addpair(int u, int v, int c)
{
	int x, y;

	x = freelist;
	freelist = next[freelist];

	y = freelist;
	freelist = next[freelist];

	ref[x] = v;
	cap[x] = c;
	rev[x] = y;
	next[x] = adj[u];
	adj[u] = x;

	ref[y] = u;
	cap[y] = 0;
	rev[y] = x;
	next[y] = adj[v];
	adj[v] = y;
}

int find()
{
	static int p[1024], s[1024];
	int i, x, t;

	for (i = 0; i < nvert; i++)
		p[i] = 0;

	p[s[0] = SOURCE] = -1;
	t = 1;

	while (p[SINK] == 0 && t-- > 0)
		for (i = adj[x = s[t]]; i != 0; i = next[i])
			if (cap[i] > 0 && p[ref[i]] == 0)
				p[s[t++] = ref[i]] = i;

	if (p[SINK] == 0)
		return 0;

	for (x = SINK; x != SOURCE; x = ref[rev[p[x]]]) {
		cap[p[x]]--;
		cap[rev[p[x]]]++;
	}

	return 1;
}

void sort(int a[], int n)
{
	int i, j, t;

	for (i = 1; i < n; i++) {
		for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
			a[j + 1] = a[j];
		a[j + 1] = t;
	}
}

int main()
{
	static int a[1024];
	int i, j, m, t;

	while (scanf("%d %d", &nsubj, &nprob) == 2 && nsubj > 0) {
		memset(adj, 0, sizeof(adj));

for (i = 0; i < MAXM; i++)
	next[i] = i + 1;
freelist = 1;

		for (i = 0; i < nsubj; i++) {
			scanf("%d", &subjc[i]);
			addpair(SUBJ(i), SINK, subjc[i]);
		}

		for (i = 0; i < nprob && scanf("%d", &m) == 1; i++) {
			addpair(SOURCE, PROB(i), 1);
			while (m-- > 0 && scanf("%d", &t) == 1)
				addpair(PROB(i), SUBJ(t - 1), 1);
		}

		nvert = 2 + nsubj + nprob;

		for (i = t = 0; i < nsubj; i++)
			t += subjc[i];

		while (find()) t--;

		if (t > 0) {
			printf("0\n");
			continue;
		}

		printf("1\n");
		for (i = 0; i < nsubj; i++) {
			for (m = 0, t = adj[SUBJ(i)]; t != 0; t = next[t])
				if (cap[t] > 0 && ref[t] >= PROB(0))
					a[m++] = ref[t] - PROB(0) + 1;

			sort(a, m);
			for (j = 0; j < m; j++)
				printf(((j + 1) < m) ? "%d " : "%d\n", a[j]);
		}
	}

	return 0;
}

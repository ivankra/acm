#include <stdio.h>
#include <string.h>

#define INF	0x7fffffff
#define MAXM	131072

int adj[128], cap[MAXM], back[MAXM], ref[MAXM], next[MAXM], n, adjcnt;
int adjid[128][128], adjgot[128][128], source, sink, testno;

int find()
{
	static int p[1024], q[1024];
	int i, j, k;

	for (i = 0; i <= n; i++)
		p[i] = 0;

	for (p[q[0] = source] = -1, j = 0, k = 1; j < k && p[sink] == 0;)
		for (i = adj[q[j++]]; i != 0; i = next[i])
			if (cap[i] > 0 && p[ref[i]] == 0)
				p[q[k++] = ref[i]] = i;

	if (p[sink] == 0)
		return 0;

	for (i = sink, k = INF; i != source; i = ref[back[p[i]]])
		if (cap[p[i]] < k) k = cap[p[i]];

	for (i = sink; i != source; i = ref[back[p[i]]]) {
		cap[p[i]] -= k;
		cap[back[p[i]]] += k;
	}

	return k;
}

int main()
{
	int i, j, m, x, y, z;

	memset(adjgot, 0, sizeof(adjgot));

	for (testno = 1; scanf("%d %d %d %d", &n, &source, &sink, &m) == 4 && n > 0; testno++) {
		for (i = 0; i <= n; i++)
			adj[i] = 0;

		while (m-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3) {
			if (x == y) continue;

			if (adjgot[x][y] != testno) {
				adjgot[x][y] = adjgot[y][x] = testno;
				adjid[x][y] = i = ++adjcnt;
				adjid[y][x] = j = ++adjcnt;

				cap[i] = cap[j] = z;

				ref[i] = y; back[i] = j;
				next[i] = adj[x]; adj[x] = i;

				ref[j] = x; back[j] = i;
				next[j] = adj[y]; adj[y] = j;
			} else {
				cap[adjid[x][y]] += z;
				cap[adjid[y][x]] += z;
			}
		}

		for (z = 0; (i = find()) > 0; z += i);
		printf("Network %d\nThe bandwidth is %d.\n\n", testno, z);
	}

	return 0;
}

#include <stdio.h>
#include <string.h>

int read(int, char *, int);

#define INF	0x7fffffff
#define MAXM	131072

int adj[128], cap[MAXM], back[MAXM], ref[MAXM], next[MAXM], n, adjcnt;
int adjid[128][128], adjgot[128][128], source, sink, testno;
int findgot[128], findid;

int find()
{
	static int p[1024], q[1024];
	int i, j, k;

	findid++;
	findgot[q[0] = source] = findid;

	for (j = 0, k = 1; j < k && findgot[sink] != findid;)
		for (i = adj[q[j++]]; i != 0; i = next[i])
			if (cap[i] > 0 && findgot[ref[i]] != findid) {
				p[q[k++] = ref[i]] = i;
				findgot[ref[i]] = findid;
			}

	if (findgot[sink] != findid)
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
	static char inbuf[4*1048576];
	static int isdig[256], m, x, y, z;
	int i, j;
	char *inp;

	for (i = '0'; i <= '9'; i++) isdig[i] = 1;
	read(0, inp = inbuf, sizeof(inbuf));

#define R(a) { while (!isdig[*inp]) inp++; \
	       for (i = *inp++ - '0'; isdig[*inp];) i = i * 10 + *inp++ - '0'; \
	       a = i; }

	memset(adjgot, 0, sizeof(adjgot));
	memset(findgot, 0, sizeof(findgot));
	findid = 1;

	for (testno = 1;; testno++) {
		R(n); if (n == 0) break;
		R(source); R(sink); R(m);

		for (i = 0; i <= n; i++)
			adj[i] = 0;

		while (m-- > 0) {
			R(x); R(y); R(z);
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

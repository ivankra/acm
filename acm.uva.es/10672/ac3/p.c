#include <stdio.h>
#include <string.h>

#define MAXN	10100
#define MAXM	10100

int read(int, char *, int);

static unsigned isdig[256], isdigz[256];
static int adjref[MAXM], adjnext[MAXM], adjfree, n;

static struct {
	int parent, adj, count, use;
} vert[MAXN];

static void mktab()
{
	register unsigned i;

	for (i = 0; i < 256; i++) isdig[i] = 0;
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	for (i = 0; i < 256; i++) isdigz[i] = isdig[i];
	isdigz[0] = 1;
}

static int insert(int list, int ref)
{
	register int k;

	k = adjfree;
	adjfree = adjnext[adjfree];

	adjref[k] = ref;
	adjnext[k] = list;

	return k;
}

static void release(int list)
{
	register int t;

	while (list != 0) {
		t = adjnext[list];
		adjnext[list] = adjfree;
		adjfree = list;
		list = t;
	}
}

static void distribute(int v)
{
	static int queue[MAXN], pred[MAXN], qhead, qtail;
	static int found[MAXN], nfound, need;
	register int i;
	int j, k;

	for (i = 1; i <= n; i++)
		pred[i] = 0;

	queue[0] = v;
	qhead = 0;
	qtail = 1;
	pred[v] = v;

	need = vert[v].count - 1;

	for (nfound = 0; qhead < qtail && nfound < need;) {
		k = queue[qhead++];

		for (i = vert[k].adj; i != 0; i = adjnext[i]) {
			j = adjref[i];
			if (pred[j] != 0)
				continue;

			pred[j] = -1;
			queue[qtail++] = j;

			if (vert[j].count == 0) {
				found[nfound] = j;
				if (++nfound >= need) break;
			}
		}

		if ((j = vert[k].parent) != 0 && pred[j] == 0) {
			pred[j] = k;
			queue[qtail++] = j;

			if (vert[j].count == 0)
				found[nfound++] = j;
		}
	}

	if (nfound > need)
		nfound = need;

	for (k = 0; k < nfound; k++) {
		i = found[k];
		vert[v].count--;
		vert[i].count++;

		while (i != v) {
			if (pred[i] < 0) {
				vert[i].use--;
				i = vert[i].parent;
			} else {
				i = pred[i];
				vert[i].use++;
			}
		}
	}
}

int main()
{
	static unsigned char inbuf[1048576];
	register unsigned char *inp;
	int i, r, v, m, d;

	mktab();

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = 0;

#define READ(var) { \
	while (!isdigz[*inp]) inp++; \
	if (*inp == 0) return 0; \
	for (var = *inp++ - '0'; isdig[*inp];) \
		var = var * 10 + *inp++ - '0'; \
}

	for (adjfree = 1, i = 1; i < MAXM; i++)
		adjnext[i] = i + 1;
	adjnext[MAXM - 1] = 0;

	for (;;) {
		READ(n);
		if (n == 0) break;

		memset(vert, '\0', sizeof(vert[0]) * (n + 1));

		for (i = 0; i < n; i++) {
			READ(v);
			READ(m);
			READ(d);

			vert[v].count = m;
			while (d-- > 0) {
				READ(m);
				vert[v].adj = insert(vert[v].adj, m);
				vert[m].parent = v;
			}
		}

		for (i = 1; i <= n; i++)
			if (vert[i].count >= 2) distribute(i);

		for (r = 0, i = 1; i <= n; i++)
			if (vert[i].use >= 0)
				r += vert[i].use;
			else
				r -= vert[i].use;

		printf("%d\n", r);

		for (i = 1; i <= n; i++)
			release(vert[i].adj);
	}

	return 0;
}

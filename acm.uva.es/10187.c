#include <stdio.h>
#include <string.h>

#define MAXN	8192
#define MAXC	131072
#define INF	0x3FFFFFFF
#define VERTEX(ct,tm) ((ct) * 24 + (tm))

int adj0[MAXN], adj1[MAXN], dist[MAXN], ref[MAXC], next[MAXC], freelist, ncities;
char city[128][64];

void search(int start)
{
	static int queue[MAXN], stk[MAXN];
	int i, j, v, qh, qt, top;

	for (j = ncities * 24, i = 0; i < j; i++)
		dist[i] = INF;

	for (dist[queue[qh = 0] = start] = 0, qt = 1; qh < qt;) {
		for (stk[0] = queue[qh], top = 1; top > 0;) {
			for (i = adj0[v = stk[--top]]; i != 0; i = next[i]) {
				if (dist[j = ref[i]] == INF) {
					dist[j] = dist[v];
					stk[top++] = j;
					queue[qt++] = j;
				}
			}
		}

		for (i = adj1[v = queue[qh++]]; i != 0; i = next[i]) {
			if (dist[j = ref[i]] == INF) {
				dist[j] = dist[v] + 1;
				queue[qt++] = j;
			}
		}
	}
}

void insert(int *a, int x)
{
	int p = freelist;
	freelist = next[p];
	ref[p] = x;
	next[p] = *a;
	*a = p;
}

void release(int *a)
{
	int p, q;

	for (p = *a; p != 0;) {
		q = next[p];
		next[p] = freelist;
		freelist = p;
		p = q;
	}

	*a = 0;
}

int get(char *s)
{
	int i;

	for (i = 0; i < ncities; i++)
		if (strcmp(city[i], s) == 0) return i;

	i = ncities++;
	strcpy(city[i], s);

	return i;
}

int main()
{
	static char s1[1024], s2[1024];
	int i, m, r, t, x, y, dep, arr, len;

	for (freelist = i = 1; i < MAXC; i++)
		next[i] = i + 1;

	memset(adj0, 0, sizeof(adj0));
	memset(adj1, 0, sizeof(adj1));

	for (scanf("%d", &r), t = 1; t <= r && scanf("%d", &m) == 1; t++) {
		for (ncities = 0; m-- > 0;) {
			scanf(" %s %s %d %d", s1, s2, &dep, &len);

			x = get(s1);
			y = get(s2);

			if (len > 12)
				continue;

			dep %= 24;
			arr = (dep + len) % 24;

			if ((6 < dep && dep < 18) || (6 < arr && arr < 18))
				continue;

			insert(&adj0[VERTEX(x, dep)], VERTEX(y, arr));
		}

		scanf(" %s %s", s1, s2);
		x = get(s1);
		y = get(s2);

		for (m = 0; m < ncities; m++) {
			for (i = 18; i != 6; i = (i + 1) % 24)
				insert(&adj0[VERTEX(m, i)], VERTEX(m, (i + 1) % 24));

			insert(&adj1[VERTEX(m, 6)], VERTEX(m, 18));
		}

		search(VERTEX(x, 18));

		for (m = dist[VERTEX(y, 0)], i = 1; i < 24; i++)
			if (dist[VERTEX(y, i)] < m) m = dist[VERTEX(y, i)];

		printf("Test Case %d.\n", t);
		if (m >= INF)
			printf("There is no route Vladimir can take.\n");
		else
			printf("Vladimir needs %d litre(s) of blood.\n", m);

		for (m = ncities * 24, i = 0; i < m; i++) {
			if (adj0[i]) release(&adj0[i]);
			if (adj1[i]) release(&adj1[i]);
		}
	}

	return 0;
}

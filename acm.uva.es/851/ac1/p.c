#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GET(s,r,c) ((int)(((s) >> ((r) * 8 + (c))) & 1))
#define SET(r,c) (1ULL << ((r) * 8 + (c)))
#define HDIV 65537
#define MAXS 1048576

typedef unsigned long long state_t;

struct {
	state_t s;
	int prev, next;
} rec[MAXS];

state_t walls, inner, space, free_inner;
int htab[HDIV], hsize, n, done;
int queue[MAXS], head, tail;

char *which(state_t s, state_t z)
{
	if (z == (((s >> 8) | (s & (walls << 8))) & free_inner))
		return "north";
	else if (z == (((s << 8) | (s & (walls >> 8))) & free_inner))
		return "south";
	else if (z == (((s >> 1) | (s & (walls << 1))) & free_inner))
		return "west";
	else
		return "east";
}

int find(state_t s)
{
	int p;

	for (p = htab[(int)(s % (state_t)HDIV)]; p != 0; p = rec[p].next)
		if (rec[p].s == s) return p;

	return 0;
}

void add(state_t s, int prev)
{
	int h, p;

	h = (int)(s % (state_t)HDIV);

	for (p = htab[h]; p != 0; p = rec[p].next)
		if (rec[p].s == s) return;

	if (++hsize >= MAXS) {printf("overflow\n");exit(1);}

	rec[hsize].s = s;
	rec[hsize].prev = prev;
	rec[hsize].next = htab[h];
	htab[h] = hsize;
	queue[tail++] = hsize;

	if (s == 0)
		done = 1;
}

void solve()
{
	static char *r[1024];
	state_t s;
	int i, k;

	memset(htab, 0, sizeof(htab));
	hsize = head = tail = done = 0;
	add(free_inner, 0);

	while (head < tail && done == 0) {
		s = rec[k = queue[head++]].s;
		add(((s >> 8) | (s & (walls << 8))) & free_inner, k);
		add(((s << 8) | (s & (walls >> 8))) & free_inner, k);
		add(((s >> 1) | (s & (walls << 1))) & free_inner, k);
		add(((s << 1) | (s & (walls >> 1))) & free_inner, k);
	}

	if (done == 0) {
		printf("impossible\n");
		return;
	}

	for (k = 0, i = find(0); rec[i].prev > 0; i = rec[i].prev)
		r[k++] = which(rec[rec[i].prev].s, rec[i].s);

	while (k-- > 0)
		printf("%s\n", r[k]);
}

int main()
{
	int i, j, c, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (walls = 0, i = 0; i < n; i++) {
			for (j = 0; j < n && (c = getchar()) != EOF;) {
				if (c == 'O')
					walls |= SET(i, j++);
				else if (c == '.')
					j++;
			}
		}

		for (space = 0, i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				space |= SET(i, j);

		for (inner = 0, i = 1; i < (n - 1); i++)
			for (j = 1; j < (n - 1); j++)
				inner |= SET(i, j);

		free_inner = (walls ^ space) & inner;

		solve();

		if (t > 0)
			printf("\n");
	}

	return 0;
}

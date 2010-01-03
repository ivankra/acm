#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define	INF	0x3FFFFFFF
#define	LEN	101000
#define	NODES	(2*LEN+1024)

char txt[LEN];
int child[NODES], sib[NODES], suflink[NODES], edge_l[NODES], edge_r[NODES];
int nodes, active_s, active_l, active_e;

int find(char *s)
{
	int i, x;

	for (x = 1;;) {
		if (*s == '\0') return 1;

		for (x = child[x];; x = sib[x]) {
			if (x == 0) return 0;
			if (txt[edge_l[x]] == *s) break;
		}

		for (i = edge_l[x]; i <= edge_r[x] && *s; i++, s++)
			if (txt[i] != *s) return 0;

		if (*s == '\0') return 1;
	}
}

void canonize(int *s, int *l, int *e, int r)
{
	int x = *s;

	while (*l <= r) {
		for (x = child[*s]; txt[edge_l[x]] != txt[*l]; x = sib[x]);

		if ((*l + edge_r[x] - edge_l[x]) > r) {
			*e = x;
			return;
		}

		*l += edge_r[x] - edge_l[x] + 1;
		*s = x;
	}
	*e = x;
}

void update(int len)
{
	int i, old, s, se, sl, x, y;

	if (len == 0) {
		nodes = 2;
		child[1] = 2;
		child[2] = sib[1] = sib[2] = 0;
		edge_l[2] = 0;
		edge_r[2] = INF;
		suflink[1] = 0;
		suflink[2] = 1;
		active_s = 1;
		active_l = 1;
		active_e = 1;
		return;
	}

	s = active_s;
	sl = active_l;
	se = active_e;
	canonize(&s, &sl, &se, len - 1);

	old = 1;

	for (;;) {
		if (sl == len) {
			if (old != 1) {
				suflink[old] = s;
				old = 1;
			}

			for (x = child[s]; x != 0; x = sib[x])
				if (txt[edge_l[x]] == txt[len]) break;

			if (x != 0) {
				active_s = s;
				active_l = len;
				active_e = x;
				return;
			}

			x = ++nodes;
			child[x] = 0;
			sib[x] = child[s];
			child[s] = x;
			edge_l[x] = len;
			edge_r[x] = INF;

			s = se = suflink[s];
			
			if (s == 0) {
				active_s = active_e = 1;
				active_l = len + 1;
				return;
			}
		} else {
			if (txt[edge_l[se] + len - sl] == txt[len]) {
				active_s = s;
				active_l = sl;
				active_e = se;
				return;
			}

			y = ++nodes;
			x = ++nodes;

			child[y] = sib[y] = 0;
			edge_l[y] = len; edge_r[y] = INF;

			if (child[s] == se) {
				child[s] = x;
			} else {
				for (i = child[s]; sib[i] != se; i = sib[i]);
				sib[i] = x;
			}

			edge_l[x] = edge_l[se];
			edge_r[x] = edge_l[se] + len - sl - 1;
			edge_l[se] += len - sl;

			child[x] = se;
			sib[x] = sib[se];
			sib[se] = y;

			if (old != 1) suflink[old] = x;
			old = x;

			if (s == 1) {
				sl++;
				se = -1;
				canonize(&s, &sl, &se, len - 1);
			} else {
				s = suflink[s];
				se = -1;
				canonize(&s, &sl, &se, len - 1);
			}
		}
	}
}

int main()
{
	static char buf[1024];
	int i, r, t;

	while (gets(buf) && sscanf(buf, "%d", &t) != 1);

	while (t-- > 0 && /*gets(txt)*/ scanf(" %s", txt) == 1) {
		child[1] = 0;
		nodes = 1;

		for (i = 0; txt[i]; i++)
			update(i);

		int n = strlen(txt);
		r = 0;
		for (i = 1; i <= nodes; i++) {
			if (edge_r[i] >= INF) edge_r[i] = n-1;
			r += edge_r[i] - edge_l[i] + 1;
		}
		printf("%d\n", r-1);
	}

	return 0;
}

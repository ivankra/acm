#include <stdio.h>

int read(int, char *, int);

#define MAXN 6000
#define MAXCELLS 20000

static int color[MAXN], uplist[MAXN], downlist[MAXN], n;
static int freelist, next[MAXCELLS], value[MAXCELLS];

#define INSERT(list, val) \
        { register int t = freelist; freelist = next[freelist]; \
	  value[t] = (val); next[t] = (list); (list) = t; }

#define FREE(list) \
        { register int t, u; \
	  for (t = (list); t != 0;) { \
	    u = next[t]; next[t] = freelist; freelist = t; t = u; } \
	  (list) = 0; }

static int dfs(int m)
{
	static int st[MAXN], sp;
	register int i, x, c;

	color[m] = 'R';

	for (st[0] = m, sp = 1; sp > 0;) {
		x = st[--sp];

		c = (color[x] == 'R') ? 'S' : ((color[x] == 'S') ? 'P' : 'R');
		for (i = downlist[x]; i != 0; i = next[i]) {
			if (color[value[i]] == 0) {
				color[value[i]] = c;
				st[sp++] = value[i];
			} else if (color[value[i]] != c) {
				return 1;
			}
		}

		c = (color[x] == 'R') ? 'P' : ((color[x] == 'S') ? 'R' : 'S');
		for (i = uplist[x]; i != 0; i = next[i]) {
			if (color[value[i]] == 0) {
				color[value[i]] = c;
				st[sp++] = value[i];
			} else if (color[value[i]] != c) {
				return 1;
			}
		}
	}

	return 0;
}

int main()
{
	static int t, r, e, x, y;
	static char inbuf[65536];
	static int isdig[256];
	register char *inptr;
	register int inleft, i;

	for (i = 0; i < 256; i++)
		isdig[i] = (i >= '0' && i <= '9');

#define READ(var, eofcode)\
{\
	for (;;) {\
		if (inleft == 0) {\
			inleft = read(0, inptr = inbuf, sizeof(inbuf));\
			if (inleft <= 0) { eofcode; break; }\
		}\
		if (isdig[(unsigned)*inptr]) break; else {inptr++; inleft--;}\
	}\
	for (var = *inptr++ - '0', inleft--;;) {\
		if (inleft == 0) {\
			inleft = read(0, inptr = inbuf, sizeof(inbuf));\
			if (inleft <= 0) { break; }\
		}\
		if (isdig[(unsigned)*inptr]) {\
			var = var * 10 + *inptr++ - '0';\
			inleft--;\
		} else {\
			break;\
		}\
	}\
}

	inptr = inbuf;
	inleft = 0;

	for (next[0] = 0, freelist = 1, i = 1; i < MAXCELLS; i++)
		next[i] = i + 1;
	next[MAXCELLS - 1] = 0;

	READ(r, { return 0; });

	for (t = 0; t++ < r;) {
		READ(n, { return 0; });
		READ(e, { return 0; });

		for (i = 1; i <= n; i++)
			color[i] = uplist[i] = downlist[i] = 0;

		while (e-- > 0) {
			READ(x, { return 0; });
			READ(y, { return 0; });

			for (i = downlist[x]; i != 0; i = next[i])
				if (value[i] == y) break;

			if (i != 0)
				continue;

			INSERT(downlist[x], y);
			INSERT(uplist[y], x);
		}

		for (i = 1, y = 0; i <= n; i++) {
			if (color[i] == 0) {
				y++;
				if (dfs(i)) break;
			}
		}

		if (i <= n)
			printf("Community %d: Conflicting Records\n", t);
		else if (y != 1)
			printf("Community %d: Not Enough Data\n", t);
		else
			printf("Community %d: Observation Complete\n", t);

		if (t == r) break;

		for (i = 1; i <= n; i++) {
			FREE(downlist[i]);
			FREE(uplist[i]);
		}
	}

	return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF 0x1FFFFFFF

int read(int, char *, int);

typedef struct {
	int a[7], c;
} tup_t;

static int cost[32], n, ntup, testid = 0;
static tup_t tup[32];

static int got[1048576], val[1048576];

static int find(int a[])
{
	int b[6], i, j, id;

	for (id = a[0], i = 1; i < n; i++)
		id = id * 10 + a[i];

	if (got[id] == testid)
		return val[id];

	got[id] = testid;

	if (id == 0)
		return val[id] = 0;

	for (val[id] = 0, i = 0; i < n; i++)
		val[id] += cost[i] * a[i];

	for (i = 0; i < ntup; i++) {
		for (j = 0;; j++) {
			if (j < n) {
				b[j] = a[j] - tup[i].a[j];
				if (b[j] < 0) break;
			} else {
				j = tup[i].c + find(b);
				if (j < val[id]) val[id] = j;
				break;
			}
		}
	}

	return val[id];
}

int main()
{
	static char inbuf[131072];
	static int a[8], t, isdig[256];
	int i, j, k;
	char *inp;

	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	i = read(0, inp = inbuf, sizeof(inbuf));
	inbuf[i++] = ' ';
	inbuf[i++] = '0';
	inbuf[i++] = ' ';

#define R(x) {while(!isdig[*inp])inp++;for(x=*inp++-'0';isdig[*inp];)x=x*10+*inp++-'0';}

	for (;;) {
		R(n);
		if (n == 0) break;

		for (i = 0; i < n; i++) {
			R(j);
			cost[i] = j;
		}

		R(j);
		ntup = j;

		for (i = 0; i < ntup;) {
			for (j = 0; j < n; j++) {
				R(k);
				tup[i].a[j] = k;
			}
			R(j);
			tup[i].c = j;

			for (j = 0; j < n && tup[i].a[j] == 0; j++);
			if (j == n) { ntup--; continue; }

			for (k = 0, j = 0; j < n; j++)
				k += tup[i].a[j] * cost[j];
			if (k <= tup[i].c) { ntup--; continue; }

			i++;
		}

		R(t);
		while (t-- > 0) {
			for (i = 0; i < n; i++) {
				R(j);
				a[i] = j;
			}
			testid++;
			printf("%d\n", find(a));
		}
	}

	exit(0);
}

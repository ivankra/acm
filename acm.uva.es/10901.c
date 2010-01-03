#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct {
	int tm, fin, bank;
	int next;
} C[16384];

int head[2], loc, glob, cap, cross, m;

int min(int a, int b) { return (a < b) ? a : b; }

void solve()
{
	int i;

	loc = 0;
	glob = 0;

	while (head[0] != 0 || head[1] != 0) {
/*printf("loc=%d glob=%d head=%d[%d]\n", loc, glob, head[loc], C[head[loc]].tm);*/

		if (head[1-loc] != 0 && C[head[1-loc]].tm <= glob &&
		    (head[loc] == 0 || (head[loc] != 0 && C[head[loc]].tm > glob))) {
			loc = 1 - loc;
			glob += cross;
			continue;
		}

		if (head[loc] == 0) {
			glob = C[head[1-loc]].tm;
			continue;
		}

		if (C[head[loc]].tm > glob) {
			if (head[1 - loc] == 0)
				glob = C[head[loc]].tm;
			else
				glob = min(C[head[loc]].tm, C[head[1-loc]].tm);
			continue;
		}

		for (i = 0; i < cap && head[loc] != 0 && C[head[loc]].tm <= glob; i++) {
			C[head[loc]].fin = glob + cross;
			head[loc] = C[head[loc]].next;
		}
/*printf("transported %d cars\n", i);*/

		loc = 1 - loc;
		glob += cross;
	}
}

int main()
{
	char s[256];
	int tail[2], i, j, c;

	for (scanf("%d", &c); c-- > 0 && scanf("%d %d %d", &cap, &cross, &m) == 3;) {
		assert(0 <= m && m < 16000);
		head[0] = head[1] = tail[0] = tail[1] = 0;

		for (i = 1; i <= m; i++) {
			scanf("%d %s", &C[i].tm, s);
			if (i > 0) assert(C[i-1].tm <= C[i].tm);

			C[i].bank = (s[0] == 'l' || s[0] == 'L') ? 0 : 1;
			C[i].next = 0;
			C[i].fin = -1;

			j = C[i].bank;
			if (tail[j] == 0) {
				head[j] = tail[j] = i;
			} else {
				C[tail[j]].next = i;
				tail[j] = i;
			}
		}

		solve();

		for (i = 1; i <= m; i++)
			printf("%d\n", C[i].fin);

		if (c > 0) printf("\n");
	}

	return 0;
}

#include <cstdio>
#include <cstring>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

int adj[32][32], pa, li, pa_next, li_next;
int vp[32], vl[32];

int next() {
//printf("pa=%c li=%c\n",pa+'A',li+'A');

	if (pa == li) {
		printf("Both annihilated in node %c\n", pa+'A');
		return 0;
	}

	vp[pa] = 1;
	vl[li] = 1;

	pa_next = pa;
	for (int i = 1; i <= 26; i++) {
		int x = (pa + i) % 26;
		if (!adj[pa][x] || x == pa || vp[x] || vl[x]) continue;
		pa_next = x;
		break;
	}

	li_next = li;
	for (int i = 1; i <= 26; i++) {
		int x =  (li + 26 - i) % 26;
		if (!adj[li][x] || x == li || vl[x]) continue;
		li_next = x;
		break;
	}

	int k = 0;
	if (pa == pa_next)
		printf("%sPaskill trapped in node %c", k++?" ":"", pa+'A');

	if (pa_next == li_next)
		printf("%sBoth annihilated in node %c", k++?" ":"", pa_next+'A');
	else if (li != li_next && li_next != pa_next && vp[li_next])
		printf("%sLisper destroyed in node %c", k++?" ":"", li_next+'A');
	else if (li == li_next)
		printf("%sLisper trapped in node %c", k++?" ":"", li+'A');

	if (k > 0) {
		printf("\n"); // [pa=%c li=%c pa'=%c li'=%c]\n",pa+'A',li+'A',pa_next+'A',li_next+'A');
		return 0;
	}

	li = li_next;
	pa = pa_next;
	return 1;
}

int main()
{
	static char line[65536];
	while (gets(line) && line[0] != '#') {
		memset(adj, 0, sizeof(adj));
		memset(vp, 0, sizeof(vp));
		memset(vl, 0, sizeof(vl));

		char *p = line, *q = line;
		for (; *p; p++)
			if (isupper(*p) || *p == '.' || *p == ':' || *p == ';') *q++ = *p;
		*q = 0;

		p = line;
		while (*p && *p != '.') {
			if (!isupper(*p)) { p++; continue; }
			int x = *p++ - 'A';
			if (*p == ':') p++;
			while (*p && isupper(*p)) {
				int y = *p++ - 'A';
				adj[x][y] = adj[y][x] = 1;
			}
		}
		if (*p == '.') p++;

		char c1, c2;
		sscanf(p, " %c %c", &c1, &c2);

		pa = c1 - 'A';
		li = c2 - 'A';

		while (next());
	}
}

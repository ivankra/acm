/*
ID: infnty1
PROB: prefix
LANG: C++
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;

#define NODES 10000

int tnext[NODES][26], tfin[NODES], tcount, textlen;
char text[200100], seen[200100];

int qdata[200100];

int solve() {
	memset(seen, 0, sizeof(seen));

	int *qhead = qdata, *qtail = qdata;
        *qtail++ = 0;

        int res = 0;
        while (qhead < qtail) {
        	int pos = *qhead++;
        	res = max(res, pos);

        	seen[pos] = 1;
        	for (int x = 0; text[pos];) {
        		x = tnext[x][text[pos++]-'A'];
        		if (x == 0) break;

        		if (tfin[x] && !seen[pos]) {
        			seen[pos] = 1;
                                *qtail++ = pos;
			}
        	}
        }

        return res;
}

int main() {
	char s[256];

	freopen("prefix.in", "r", stdin);
	freopen("prefix.out", "w", stdout);

	memset(tnext, 0, sizeof(tnext));
	memset(tfin, 0, sizeof(tfin));
	tcount = 1;

	while (scanf(" %s", s) == 1 && s[0] != '.') {
		int x = 0;
		for (int i = 0; s[i]; i++) {
			int c = toupper(s[i]) - 'A';
			if (tnext[x][c] == 0)
				tnext[x][c] = ++tcount;
			x = tnext[x][c];
		}
		tfin[x] = 1;
	}

	for (textlen = 0; scanf(" %[A-Z]", text+textlen) == 1;)
		textlen += strlen(text+textlen);

	printf("%d\n", solve());

	return 0;
}

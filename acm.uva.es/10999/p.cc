#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

#define NODES 1000010

int kid[NODES], sib[NODES], cnt;
char alpha[NODES], flag[NODES];

void insert(char *s) {
	int x, y;
	for (x = 0; *s; s++, x = y) {
		for (y = kid[x]; y != 0 && alpha[y] != *s; y = sib[y]);
		if (y != 0) continue;
		y = cnt++;
		alpha[y] = *s;
		sib[y] = kid[x];
		kid[x] = y;
		flag[y] = 0;
	}
	flag[x] = 1;
}

int look(char *s) {
	int x, y;
	for (x = 0; *s; s++, x = y) {
		for (y = kid[x];; y = sib[y]) {
			if (y == 0) return 0;
			if (alpha[y] == *s) break;
		}
	}
	return flag[x];
}

struct Tile { char c; int x; } tile[16];
int cmp(const Tile &a, const Tile &b) {
	return (a.c < b.c || (a.c == b.c && a.x < b.x));
}

int main()
{
	static char buf[65536];
	int n, T;

	cnt = 1;
	kid[0] = sib[0] = 0;
	flag[0] = 1;

	scanf("%d", &n);
	assert(1 <= n && n <= 100000);
	while (n-- > 0 && scanf("%s", buf)) {
		int k = strlen(buf);
		if (k > 10) continue;
		for (int i = 0; i < k; i++) {
			int x = buf[i], j;
			for (j = i-1; j >= 0 && buf[j] > x; j--)
				buf[j+1] = buf[j];
			buf[j+1] = x;
		}
		insert(buf);
	}

	for (scanf("%d", &T); T-- > 0 && scanf("%d", &n) == 1;) {
		assert(1 <= n && n <= 10);
		for (int i = 0; i < n; i++)
			scanf(" %c %d", &tile[i].c, &tile[i].x);
		sort(tile, tile+n, cmp);

		int best = 0;
		for (int m = 0; m < (1 << n); m++) {
			int sum = 0, i, j;
			for (i = j = 0; i < n; i++) {
				if (m & (1 << i)) {
					sum += tile[i].x;
					buf[j++] = tile[i].c;
				}
			}
			buf[j] = '\0';
			if (sum > best && look(buf)) best = sum;
		}

		printf("%d\n", best);
	}

	return 0;
}

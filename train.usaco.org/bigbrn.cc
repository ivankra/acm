/*
ID: infnty1
PROB: bigbrn
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char a[1024][1024];
int N;

int main() {
	freopen("bigbrn.in", "r", stdin);
	freopen("bigbrn.out", "w", stdout);

	memset(a, 0, sizeof(a));

	int T, y, x;
	scanf("%d %d", &N, &T);
	while (T-- > 0 && scanf("%d %d", &y, &x) == 2)
		a[y][x] = 1;

	int up[1024], sq[1024];
	memset(up, 0, sizeof(up));
	memset(sq, 0, sizeof(sq));

	int best = 0;

	for (int r = 1; r <= N; r++) {
		int left = 0, prev = 0;
		for (int c = 1; c <= N; c++) {
			if (a[r][c]) {
				up[c] = sq[c] = left = 0;
			} else {
				up[c]++;
				left++;
				int t = sq[c];
				sq[c] = min(prev+1, min(left, up[c]));
				prev = t;
				best = max(best, sq[c]);
			}
		}
	}

	printf("%d\n", best);
}

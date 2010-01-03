/*
ID: infnty1
PROB: frameup
LANG: C++
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;

int W, H, a[32][32], dep[32], all;
struct Rect { int x1, x2, y1, y2; } R[32];

char out[32];

void doit(int k, int seen) {
	if (seen == all) {
		out[k] = 0;
		printf("%s\n", out);
	} else {
		for (int c = 0; c < 26; c++) {
			if (((all >> c) & 1) == 1 &&
			    ((seen >> c) & 1) == 0 &&
			    (seen & dep[c]) == dep[c]) {
				out[k] = 'A' + c;
				doit(k+1, seen | (1 << c));
			}
		}
	}
}

int main()
{
	freopen("frameup.in", "r", stdin);
	freopen("frameup.out", "w", stdout);

	scanf("%d %d", &H, &W);

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W;) {
			a[i][j] = getchar();
			if (a[i][j] == '.' || isupper(a[i][j])) j++;
		}
	}

	all = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (a[i][j] == '.') continue;

			Rect &r = R[a[i][j]-'A'];
			if (((all >> (a[i][j] - 'A')) & 1) == 0) {
				r.y1 = r.y2 = i;
				r.x1 = r.x2 = j;
				all |= 1 << (a[i][j] - 'A');
			} else {
				r.y1 <?= i; r.y2 >?= i;
				r.x1 <?= j; r.x2 >?= j;
			}
		}
	}

	memset(dep, 0, sizeof(dep));
	for (int k = 0; k < 26; k++) {
		if (((all >> k) & 1) == 0) continue;
		Rect &r = R[k];
		for (int y = r.y1; y <= r.y2; y++)
		for (int x = r.x1; x <= r.x2; x++)
		if (a[y][x] != '.' && a[y][x] != 'A'+k)
		if (x == r.x1 || x == r.x2 || y == r.y1 || y == r.y2)
			dep[a[y][x]-'A'] |= 1 << k;
	}

	doit(0, 0);

	return 0;
}


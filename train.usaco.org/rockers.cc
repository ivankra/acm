/*
ID: infnty1
PROB: rockers
LANG: C++
*/
#include <cstdio>
#include <cstring>

int N, T, M, len[32], memo[32][32][32];

int f(int i, int tl, int ml) {
	int &res = memo[i][tl][ml];
	if (res != -1) return res;
	res = 0;
	if (i >= N) return res = 0;
	if (ml > 0) res >?= f(i, T, ml-1);
	res >?= f(i+1, tl, ml);
	if (tl >= len[i]) res >?= 1 + f(i+1, tl-len[i], ml);
	return res;
}

int main() {
	freopen("rockers.in", "r", stdin);
	freopen("rockers.out", "w", stdout);

	scanf("%d %d %d", &N, &T, &M);
	for (int i = 0; i < N; i++) scanf("%d", &len[i]);

	memset(memo, 0xff, sizeof(memo));
	printf("%d\n", f(0, 0, M));
}

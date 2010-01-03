/*
ID: infnty1
PROB: latin
LANG: C++
*/
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

int C[16], R[16], N, all, res=0, low[1024];

void rec(int r, int c) {
	if (c > N) { r++; c = 2; }
	if (r > N) { res++; return; }

	for (int m = all ^ (R[r] | C[c]); m != 0; m &= m-1) {
		int x = low[m];
		R[r] |= 1 << x; C[c] |= 1 << x;
		rec(r, c+1);
		R[r] &= ~(1 << x); C[c] &= ~(1 << x);
	}
}

long long fact(int n) { return n==0 ? 1 : fact(n-1)*n; }

int main() {
	freopen("latin.in", "r", stdin);
	freopen("latin.out", "w", stdout);

	scanf("%d", &N);

	all = ((1<<N)-1) << 1;
	for (int m = 1; m < 1024; m++)
		for (low[m] = 0; ((m >> low[m]) & 1) == 0; low[m]++);

	long long ans = 0;
	map<int, int> memo;

	int b[16], c[16], d[16];
	for (int i = 1; i <= N; i++) b[i] = i;
	swap(b[1], b[2]);

	do {
		int ok = 1;
		for (int i = 1; i <= N; i++)
			if (b[i] == i) { ok = 0; break; }
		if (!ok) continue;

		for (int i = 1; i <= N; i++) c[i] = 0;

		int m = 0;
		for (int i = 1; i <= N; i++) {
			if (c[i]) continue;
			d[m] = 0;
			for (int x = i; c[x] == 0; x = b[x])
				d[m]++, c[x] = 1;
			m++;
		}
		sort(d, d+m);

		int id = 0;
		for (int i = 0; i < m; i++)
			id = id*(N+1) + d[i];

		if (memo.count(id) == 0) {
			for (int i = 2; i <= N; i++) {
				R[i] = 1 << i;
				C[i] = (1 << i) | (1 << b[i]);
			}
			res = 0;
			rec(3, 2);
			memo[id] = res;
		}

		ans += memo[id];
	} while (next_permutation(b+2, b+N+1));

	printf("%lld\n", fact(N-1)*ans);
}

/*
 *     N  answers        res
 *     2  1              1
 *     3  2              1
 *     4  24             4
 *     5  1344           56
 *     6  1128960        9408
 *     7  12198297600    16942080
 */

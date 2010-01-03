/*
ID: infnty1
PROB: nuggets
LANG: C++
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define INF 0x1fffffff

int main()
{
	int a[16], n;

	freopen("nuggets.in", "r", stdin);
	freopen("nuggets.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);

	sort(a, a+n);

	int mod = a[0];
	vector<int> S(mod, INF);
	
	/* S[i] = smallest size s of a box, such that all boxes of sizes s+i+mod*t, t >= 0
	   are representable */

	for (int i = 0; i < n; i++)
		S[a[i] % mod] <?= a[i];

	int change = 0;
	do {
		change = 0;
		for (int i = 0; i < mod; i++) {
			if (S[i] == INF) continue;
			for (int j = 0; j < n; j++) {
				int t = S[i] + a[j];
				if (t < S[t % mod]) {
					S[t % mod] = t;
					change = 1;
				}
			}
		}
	} while (change);

	int best = 0;
	for (int i = 0; i < mod; i++) {
		if (S[i] == INF) { best = 0; break; }
		best >?= S[i] - mod;
	}

	printf("%d\n", best);

	return 0;
}

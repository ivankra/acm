#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <cmath>
#include <cassert>
#include <bitset>
using namespace std;
typedef vector<int> VI;

int cons[128][128], A, S, street[110];
int dp[128][128];
bitset<128> dp_aves[128][128], avenue[128];

void solve()
{
	for (int a = 1; a <= 100; a++) {
		avenue[a].reset();
		for (int i = 0; i < S-1; i++) {
			for (int s = street[i]; s < street[i+1]; s++) {
				if (cons[a][s]) avenue[a].set(i);
			}
		}
	}

	for (int a = 0; a <= 100; a++) dp[1][a] = -1000000;
	dp[1][1] = 0;
	dp_aves[1][1].reset();

	for (int R = 2; R <= 100; R++) {
		dp[R][0] = dp[R][1] = -1000000;
		for (int K = 2; K <= A; K++) {
			dp[R][K] = -1000000;

			bitset<128> bs;
			for (int rr = R-1; rr >= 1; --rr) {
				bs |= avenue[rr];

				int t = dp[rr][K-1] + bs.count();
				if (t > dp[R][K]) {
					dp[R][K] = t;
					dp_aves[R][K] = dp_aves[rr][K-1];
					dp_aves[R][K].set(rr);
				}
			}
		}
	}

//printf("[%d]\n", dp[100][A]);

	bitset<128> bs = dp_aves[100][A];
	bs.set(1);
	bs.set(100);

	printf("%d", bs.count());
	for (int i = 1; i <= 100; i++)
		if (bs.test(i)) printf(" %d", i);
	printf("\n");
}

int main()
{
	int N, s, a;
	while (scanf("%d", &N) == 1 && N >= 0) {
		memset(cons, 0, sizeof(cons));
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &s, &a);
			cons[a][s] = 1;
		}

		scanf("%d", &S);
		for (int i = 0; i < S; i++)
			scanf("%d", &street[i]);
		sort(street, street + S);

		scanf("%d", &A);

		solve();
	}
}

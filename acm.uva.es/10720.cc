#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

int deg[20000], N;
int cnt[20000];

bool solve()
{
	int sum = 0;
	for (int i = 0; i < N; i++) {
		if (deg[i] < 0 || deg[i] >= N) return false;
		sum += deg[i];
	}
	if (sum % 2 != 0) return false;

	for (int i = 0; i <= N; i++) cnt[i] = 0;
	for (int i = 0; i < N; i++) ++cnt[deg[i]];

	for (int d = N-1; d >= 1;) {
		if (cnt[d] == 0) {
			d--;
			continue;
		}

		--cnt[d];

		int s = d, a = 0, i, c;
		for (i = d; i > 0; i--) {
			c = min(cnt[i], s);
			cnt[i] += a;
			a = 0;

			s -= c;
			cnt[i] -= c;
			a += c;

			if (s == 0) {
				cnt[i-1] += a;
				break;
			}
		}

		if (s != 0) return false;
	}

	return true;
}

int main()
{
	while (scanf("%d", &N) == 1 && N > 0) {
		for (int i = 0; i < N; i++) scanf("%d", &deg[i]);
		printf(solve() ? "Possible\n" : "Not possible\n");
	}
}

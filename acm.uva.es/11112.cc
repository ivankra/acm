#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>

int s, bet, t;

int solve() {
	if (s == t) return 0;
//	if (s < bet) return -1;

	int diff = abs(s - t);
	int ans = (diff + 3*bet - 1) / (3*bet);

	if (t == 0)
		return ans;

	if ((diff % bet) != 0) return -1;
	return ans;
}

int main() {
	while (scanf("%d %d %d", &s, &bet, &t) == 3 && (s|bet|t) != 0) {
		assert(s > 0 && bet > 0 && t >= 0);

		int res = solve();
		if (res < 0)
			printf("No accounting tablet\n");
		else
			printf("%d\n", res);		
	}
}

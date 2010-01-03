#include <algorithm>
#include <vector>
#include <sstream>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cctype>
using namespace std;

int x[10010], cnt[10010], m, n;

int solve() {
	for (int i = 0; i < m; i++) cnt[i] = 0;
	cnt[0] = 1;

	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum = (sum + x[i]) % m;
		cnt[sum]++;
	}

	int res = 0;
	for (int i = 0; i < m; i++)
		res += cnt[i] * (cnt[i]-1) / 2;
	return res;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		int b, c;
		scanf("%d %d %d %d %d", &x[0], &b, &c, &m, &n);
		x[0] %= m;
		for (int i = 1; i < n; i++)
			x[i] = (x[i-1] * b + c + 1) % m;
		printf("Case %d: %d\n", cs, solve());
	}
}

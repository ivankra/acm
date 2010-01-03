// greedy
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <queue>
using namespace std;

int main()
{
	int T, N;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		vector<int> a(N), b(N);
		for (int i = 0; i < N; i++) scanf("%d", &a[i]);
		for (int i = 0; i < N; i++) scanf("%d", &b[i]);
		sort(a.begin(), a.end());
		sort(b.begin(), b.end());

		long long res = 0;
		for (int i = 0; i < N; i++)
			res += a[i] * (long long)b[i];
		cout << res << endl;
	}
}

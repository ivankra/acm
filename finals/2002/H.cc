#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
typedef long long LL;

int N, a[1024], b[1024], pos[1024], seen[1024], gm;

int main()
{
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		gm = INT_MAX;
		for (int i = 0; i < N; i++) {
			scanf("%d", &a[i]);
			b[i] = a[i];
			gm = min(gm, a[i]);
		}

		sort(b, b+N);
		for (int i = 0; i < N; i++)
			pos[b[i]] = i;

		int res = 0;
		memset(seen, 0, sizeof(seen));

		for (int i = 0; i < N; i++) {
			if (seen[i]) continue;

			int m = a[i], n = 0, sum = 0;
			for (int j = i; !seen[j]; j = pos[a[j]]) {
				n++;
				m = min(m, a[j]);
				sum += a[j];
				seen[j] = 1;
			}

			res += min(sum-m + (n-1)*m, sum-m + 2*m + (n+1)*gm);
		}

		printf("Case %d: %d\n\n", cs, res);
	}
}

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct HairyBusiness {
	int getMaximumProfit (vector<int> cost) {
		int f[128], g[128], n = cost.size();

		for (int i = 1; i <= n; i++) f[i] = -1;
		f[0] = 0;

		for (int d = 0; d < n; d++) {
			for (int i = n; i >= 0; i--) f[i+1] = f[i];
			f[0] = -1;

			for (int i = 1; i <= n+1; i++)
				if (f[i] >= 0)
					f[0] >?= f[i] + i * cost[d];
		}

		return f[0];
	}
};

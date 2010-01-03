#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long i64;

i64 best[128][384];
i64 ab(i64 x) { return x < 0 ? -x : x; }

struct NotchedApproximation {
	long long getApproxDegree (vector<int> A) {
		vector<i64> val;
		int n = A.size();

		for (int i = 0; i < n; i++) {
			val.push_back(A[i]);
			val.push_back(A[i]-1);
			val.push_back(A[i]+1);
		}
		sort(val.begin(), val.end());
		val.erase(unique(val.begin(), val.end()), val.end());
		int m = val.size();

		memset(best, 0, sizeof(best));

		for (int k = 1; k <= n; k++) {
			for (int t = 0; t < m; t++) {
				int mi, ma;

				if ((k-1) & 1) {
					mi = t+1;
					ma = m-1;
				} else {
					mi = 0;
					ma = t-1;
				}

				best[k][t] = 1LL<<60;
				for (int s = mi; s <= ma; s++)
					best[k][t] <?= best[k-1][s] + ab(A[k-1]-val[s]);
			}
		}

		i64 res = 1LL<<60;
		for (int t = 0; t < m; t++)
			res <?= best[n][t];
		return res;
	}
};

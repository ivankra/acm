/*
ID: infnty1
PROB: ariprog
LANG: C++
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

int is[131072], bi[65536], n, m, bimax;

int main()
{
	freopen("ariprog.in", "r", stdin);
	freopen("ariprog.out", "w", stdout);

	scanf("%d %d", &n, &m);

	memset(is, 0, sizeof(is));
	for (int p = 0; p <= m; p++)
		for (int q = 0; q <= m; q++)
			is[p*p+q*q] = 1;
	bimax = 2 * m * m;

	m = 0;
	for (int i = 0; i < 131072; i++)
		if (is[i]) { bi[m++] = i; is[i] = m; }

	vector<pair<int,int> > R;

	for (int i = 0; i < m; i++) {
		for (int j = i+1; j < m; j++) {
			int d = bi[j] - bi[i];
			int last = bi[i] + d * (n - 1);
			if (last > bimax) break;

			if (is[last] == 0) continue;

			int k, x = bi[j] + d;
			for (k = 2; k < n && is[x]; k++, x += d);
			if (k < n) continue;

			R.push_back(pair<int,int>(d, bi[i]));
		}
	}

	sort(R.begin(), R.end());
	for (int i = 0; i < (int)R.size(); i++)
		printf("%d %d\n", R[i].second, R[i].first);

	if (R.empty()) printf("NONE\n");

	return 0;
}

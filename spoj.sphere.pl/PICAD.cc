#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	int c1, c2, N;
	while (scanf("%d %d %d", &c1, &c2, &N) == 3) {
		c1 *= 2;
		c2 *= 2;
		vector<pair<int, int> > v;
		v.push_back(make_pair(c1, 0));
		v.push_back(make_pair(c2, 0));
		for (int i = 0; i < N; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			v.push_back(make_pair(2*a-1, +1));
			v.push_back(make_pair(2*b+1, -1));
		}
		sort(v.begin(), v.end());

		int resMin = N, resMax = 0;
		int cur = 0;

		for (int i = 0; i < (int)v.size(); i++) {
			if (c1 <= v[i].first && v[i].first <= c2) {
				resMin = min(resMin, cur);
				resMax = max(resMax, cur);
			}
			cur += v[i].second;
		}

		printf("%d %d\n", resMin, resMax);
	}
}

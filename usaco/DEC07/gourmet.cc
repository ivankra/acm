/*
TASK: gourmet
LANG: C++
ID: infnty1
*/
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

typedef pair<int, int> Pair;

int main()
{
	assert(freopen("gourmet.in", "r", stdin) != NULL);
	assert(freopen("gourmet.out", "w", stdout) != NULL);

	int N, M;
	scanf("%d %d", &N, &M);

	vector<Pair> cows(N), grass(M);

	for (int i = 0; i < N; i++)
		scanf("%d %d", &cows[i].first, &cows[i].second);

	for (int i = 0; i < M; i++)
		scanf("%d %d", &grass[i].first, &grass[i].second);

	// sort everything by price
	sort(cows.begin(), cows.end());
	sort(grass.begin(), grass.end());

	int i = 0, j = 0;
	long long res = 0;
	set<Pair> cset;

	// greedily match grass packages with cows in order of increasing cost
	for (; i < (int)grass.size(); i++) {
		int curCost = grass[i].first;
		int curGreen = grass[i].second;

		while (j < (int)cows.size() && cows[j].first <= curCost) {
			cset.insert(Pair(cows[j].second, j));
			j++;
		}

		if (cset.size() != 0) {
			int g = cset.begin()->first;
			if (g <= curGreen) {
				cset.erase(cset.begin());
				res += curCost;
			}
		}
	}

	if (j != (int)cows.size() || cset.size() != 0) {
		printf("IMPOSSIBLE\n");
	} else {
		printf("%lld\n", res);
	}
}

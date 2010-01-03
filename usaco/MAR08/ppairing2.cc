/*
ID: infnty1
LANG: C++
TASK: ppairing
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
using namespace std;

int deg[200000], N;

struct Cmp {
	bool operator()(int x, int y) const {
		return deg[x] != deg[y] ? (deg[x] > deg[y]) : (x < y);
	}
};

int main()
{
	assert(freopen("ppairing.in", "r", stdin) != NULL);
	assert(freopen("ppairing.out", "w", stdout) != NULL);

	scanf("%*d %d", &N);
	for (int x = 1; x <= N; x++)
		scanf("%d", &deg[x]);

	set<int, Cmp> V;
	for (int x = 1; x <= N; x++)
		if (deg[x] != 0) V.insert(x);

	while (V.size() > 1) {
		int x = *V.begin();
		V.erase(V.begin());

		int y = *V.begin();
		V.erase(V.begin());

		printf("%d %d\n", x, y);
		--deg[y];
		--deg[x];

		if (deg[x] != 0) V.insert(x);
		if (deg[y] != 0) V.insert(y);
	}
}


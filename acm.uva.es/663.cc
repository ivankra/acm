// maximum bipartite matching.
// To determine whether an matched edge (x, y) must be present in all perfect
// matchings, try to find an augmenting path from x to y in the graph without it.
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

int N;
int xmin[30], xmax[30], ymin[30], ymax[30], X[30], Y[30];
int xmatch[30], ymatch[30];
int seen[30], seenId = 42;

bool adj(int i, int j) {
	return
		xmin[i] < X[j] && X[j] < xmax[i] &&
		ymin[i] < Y[j] && Y[j] < ymax[i];
}

bool dfs(int x)
{
	if (seen[x] == seenId) return false;
	seen[x] = seenId;
	for (int y = 0; y < N; y++) {
		if (adj(x, y) && (ymatch[y] < 0 || dfs(ymatch[y]))) {
			xmatch[x] = y;
			ymatch[y] = x;
			return true;
		}
	}
	return false;
}

bool dfs2(int x, int s, int t)
{
	if (seen[x] == seenId) return false;
	seen[x] = seenId;
	for (int y = 0; y < N; y++) {
		if (x == s && y == t) continue;
		if (adj(x, y) && (y == t || dfs2(ymatch[y], s, t))) {
			return true;
		}
	}
	return false;
}

int main()
{
	for (int cs = 1; cin >> N; cs++) {
		if (N == 0) break;
		assert(1 <= N && N <= 26);

		for (int i = 0; i < N; i++)
			cin >> xmin[i] >> xmax[i] >> ymin[i] >> ymax[i];
		for (int i = 0; i < N; i++)
			cin >> X[i] >> Y[i];

		printf("Heap %d\n", cs);

		memset(xmatch, 0xff, sizeof(xmatch));
		memset(ymatch, 0xff, sizeof(ymatch));

		int maxMatch = 0, determined = 0;
		for (int x = 0; x < N; x++) {
			seenId++;
			if (dfs(x)) maxMatch++;
		}

		if (maxMatch == N) {
			for (int x = 0; x < N; x++) {
				seenId++;
				if (!dfs2(x, x, xmatch[x])) {
					if (determined++) printf(" ");
					printf("(%c,%d)", x+'A', xmatch[x]+1);
				}
			}
		}

		if (determined == 0) printf("none");
		printf("\n\n");
	}
}

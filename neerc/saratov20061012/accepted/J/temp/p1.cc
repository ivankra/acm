// Another fine solution by Stavropol SU #1 team ;)
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

int parent[200010], parentColored[200010], N;
int edgeId[200010];
vector<int> kids[200010];
vector<int> out;

int depth[200010], kidsDepths[200010], need[200010], needMax[200010];
int above[200010];  // # of colored edges from x to root

void outDfs(int x, int a) {
	if (x > 1 && !parentColored[x] && a < needMax[x]) {
		out.push_back(edgeId[x]);
		a++;
	}

	for (int i = 0; i < (int)kids[x].size(); i++) {
		int y = kids[x][i];
		outDfs(y, a);
	}
}

void dfs(int x) {
	if (x == 1) {
		depth[x] = 0;
		above[x] = 0;
	} else {
		depth[x] = depth[parent[x]] + 1;
		above[x] = above[parent[x]] + parentColored[x];
	}
	kidsDepth[x] = depth[x];

	if (2*above[x] >= depth[x]) {
		need[x] = 0;
	} else {
		//x >= (d - 2a)/2
		need[x] = (depth[x] - 2 * above[x] + 1) / 2;
	}

	needMax[x] = need[x];

	for (int i = 0; i < (int)kids[x].size(); i++) {
		int y = kids[x][i];
		dfs(y);

		if (depth[y] > kidsDepth[x])
			kidsDepth[x] = depth[y];

		if (needMax[y] > needMax[x])
			needMax[x] = needMax[y];
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d", &N);
	memset(parent, 0, sizeof(parent));
	memset(parentColored, 0, sizeof(parentColored));
	for (int i = 1; i <= N; i++) kids[i].clear();

	for (int i = 1; i <= N; i++) {
		static char buf[1000];
		int x, y;
		scanf(" %d %d %s", &x, &y, buf);

		parent[x] = y;
		edgeId[x] = i;
		if (strcmp(buf, "protected") == 0) {
			parentColored[x] = 1;
		} else {
			parentColored[x] = 0;
			scanf(" %s", buf);
		}

		kids[y].push_back(x);
	}

	dfs(1);

	out.clear();

	outDfs(1, 0);
	printf("%d\n", out.size());
	for (int i = 0; i < (int)out.size(); i++)
		printf(i==0 ? "%d" : " %d", out[i]);
	printf("\n");

	return 0;
}
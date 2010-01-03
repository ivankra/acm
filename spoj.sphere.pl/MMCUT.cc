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
const double PI = 2 * acos(0.0);

int color[100100], N;
vector<int> adj[100100];
vector<int> black;

bool dfs(int x) {
	for (int i = 0; i < (int)adj[x].size(); i++) {
		int y = adj[x][i];
		if (color[y] == -1) {
			color[y] = 1 - color[x];
			dfs(y);
		} else if (color[y] != 1 - color[x]) {
			return false;
		}
	}
	return true;
}

bool bicolor()
{
	memset(color, 0xff, sizeof(color));

	for (int i = 0; i < (int)black.size(); i++) {
		int x = black[i];
		if (color[x] == -1) {
			color[x] = 1;
			if (!dfs(x)) return false;
		} else if (color[x] != 1) {
			return false;
		}
	}

	for (int i = 0; i < N-1; i++) {
		if (color[i] == -1) {
			color[i] = 1;
			if (!dfs(i)) return false;
		}
	}

	return true;
}

int main()
{
	int K;
	scanf("%d %d", &N, &K);

	assert(N <= 100000);
	assert(K <= 100000);
	if (N <= 1 || K <= 0) {
		printf("0\n");
		return 0;
	}

	for (int i = 0; i < K; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a > b) swap(a, b);
		assert(a != b);
		assert(0 <= a && a < b && b <= N-1);

		if (b == N-1) {
			black.push_back(a);
		} else {
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
	}

	if (bicolor()) {
		printf("1\n");
	} else {
		printf("2\n");
	}
}

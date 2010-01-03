#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
#define SIZE(x) int((x).size())
#define FOREACH(it, x) for(__typeof((x).begin())it=(x).begin();it!=(x).end();++it)
typedef long long LL;
typedef vector<int> VI;

#define MAX 110000

int tree[MAX], N, totalSum;

void treeInc(int x) {
	for (int i = x; i < N; i |= i + 1) ++tree[i];
}

int treeSum(int x) {
	int res = 0;
	while (x >= 0) {
		res += tree[x];
		x = (x & (x + 1)) - 1;
	}
	return res;
}

int remains(int from) {
	return (N-from) - (totalSum - treeSum(from-1));
}

int main()
{
	scanf("%d", &N);

	memset(tree, 0, sizeof(tree));
	totalSum = 0;

	int answer = 0, from;
	for (int i = 0; i < N; i++) {
		scanf("%d", &from);
		from--;

		int z = remains(from);
		if (z == 0) {
			answer++;
			continue;
		}

		int left = from, right = N;
		while (right - left > 1) {
			int mid = (left + right) / 2;
			if (remains(mid) == z)
				left = mid;
			else
				right = mid;
		}
//printf("driver %d => %d\n", i+1, left+1);
		treeInc(left);
		totalSum++;
	}

	printf("%d\n", answer);
}

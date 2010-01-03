#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 200010

struct Node {
	int left, right, size, count;
} tree[MAX];

int buildTree(int a, int b) {
	if (a > b) {
		return 0;
	} else {
		int x = (a + b) / 2;
		tree[x].left = buildTree(a, x-1);
		tree[x].right = buildTree(x+1, b);
		tree[x].size = b - a + 1;
		tree[x].count = 1;
		return x;
	}
}

int extract(int x, int k) {
	int leftSize = tree[tree[x].left].size;
	int res;
	if (k < leftSize) {
		res = extract(tree[x].left, k);
	} else if (k < leftSize + tree[x].count) {
		res = x;
		tree[x].count--;
	} else {
		res = extract(tree[x].right, k - leftSize - tree[x].count);
	}
	tree[x].size = tree[tree[x].left].size + tree[x].count + tree[tree[x].right].size;
	return res;
}

int a[MAX], N;

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%d", &a[i]);

		tree[0].size = 0;
		int root = buildTree(1, N);

		for (int i = N; i >= 1; i--)
			a[i] = extract(root, i - 1 - a[i]);

		for (int i = 1; i <= N; i++)
			printf(i == 1 ? "%d" : " %d", a[i]);
		printf("\n");
	}
}

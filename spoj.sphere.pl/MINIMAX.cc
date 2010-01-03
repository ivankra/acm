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
int tree[200010];

void update(int root, int a, int b, int index, int newValue) {
	if (a == b) {
		assert(a == index);
		if (newValue < tree[root])
			tree[root] = newValue;
	} else {
		int c = (a + b) / 2;
		if (index <= c)
			update(2*root, a, c, index, newValue);
		else
			update(2*root+1, c+1, b, index, newValue);
		tree[root] = min(tree[2*root], tree[2*root+1]);
	}
}

void update(int index, int newValue) {
	update(1, 1, N, index, newValue);
}

int getMin(int root, int a, int b, int qa, int qb) {
	if (qa < a) qa = a;
	if (qb > b) qb = b;
	if (qa > qb) return 0x3fffffff;
	if (a == qa && b == qb) return tree[root];
	int c = (a + b) / 2;
	return min(getMin(2*root, a, c, qa, qb), getMin(2*root+1, c+1, b, qa, qb));
}

int getMin(int a, int b) {
	return getMin(1, 1, N, a, b);
}

int main()
{
	int T, M;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &N, &M);

		for (int i = 1; i <= 4*N; i++)
			tree[i] = 0x3fffffff;
		update(1, 0);

		for (int i = 1; i <= M; i++) {
			int x, y;
			scanf("%d %d", &x, &y);

			update(y, 1 + getMin(x, N));
		}

		printf("%d\n", getMin(N, N));
	}
}

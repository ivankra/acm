#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Node {
	int endVal, minVal;
} tree[65536];

char word[31000];
int updatePos;

void update(int r, int a, int b) {
	if (updatePos != 0 && (updatePos < a || updatePos > b)) return;
	if (a == b) {
		tree[r].endVal = word[a] == '(' ? +1 : -1;
		tree[r].minVal = tree[r].endVal;
	} else {
		int c = (a + b) >> 1;
		update(2*r, a, c);
		update(2*r+1, c+1, b);
		tree[r].endVal = tree[2*r].endVal + tree[2*r+1].endVal;
		tree[r].minVal = min(tree[2*r].minVal, tree[2*r].endVal + tree[2*r+1].minVal);
	}
}

int main()
{
	int N, Q;
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		for (int i = 1; i <= N; i++) {
			int c;
			do { c = getchar(); } while (c != ')' && c != '(');
			word[i] = c;
		}

		updatePos = 0;
		update(1, 1, N);

		printf("Test %d:\n", cs);
		scanf("%d", &Q);
		for (int q = 1; q <= Q; q++) {
			scanf("%d", &updatePos);
			if (updatePos == 0) {
				printf(tree[1].endVal == 0 && tree[1].minVal == 0 ? "YES\n" : "NO\n");
			} else {
				word[updatePos] = word[updatePos] == '(' ? ')' : '(';
				update(1, 1, N);
			}
		}
	}
}

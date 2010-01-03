#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>
using namespace std;

int seq[32000], N;
int val1[32000], tree1[32000];
int val2[32000], tree2[32000];

int query(int lo, int hi,  int tree[], int val[], int a, int b) {
	lo >?= a; hi <?= b;
	if (lo > hi) return 0;
	if (a == b) return val[a];
	int mid = (a + b) / 2;
	if (a == lo && b == hi) return tree[mid];
	return max(query(lo, hi, tree, val, a, mid), query(lo, hi, tree, val, mid+1, b));
}

void update(int index, int newValue, int tree[], int val[], int a, int b) {
	if (a == b) {
		assert(index == a && newValue >= val[index]);
		val[index] = newValue;
	} else {
		int mid = (a + b) / 2;
		tree[mid] >?= newValue;
		if (index <= mid)
			update(index, newValue, tree, val, a, mid);
		else
			update(index, newValue, tree, val, mid+1, b);
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			 scanf("%d", &seq[i]);

		memset(val1, 0, sizeof(val1));
		memset(tree1, 0, sizeof(tree1));
		memset(val2, 0, sizeof(val2));
		memset(tree2, 0, sizeof(tree2));

		int best = 0;
		for (int i = 0; i < N; i++) {
			int t = 1 + query(0,seq[i]-1, tree2,val2,0,N+1);
			update(seq[i],t, tree1,val1,0,N+1);
			best >?= t;

			t = 1 + query(seq[i]+1,N+1, tree1,val1,0,N+1);
			if (t > 1) {
				update(seq[i],t, tree2,val2,0,N+1);
				best >?= t;
			}
		}

		printf("%d\n", best);
	}
}

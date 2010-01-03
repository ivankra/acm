#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

struct Box {
	int a[3], h;

	bool operator <(const Box &other) const {
		return a[0] < other.a[0];
	}
};

int main()
{
	int n;

	while (scanf("%d", &n) == 1 && n > 0) {
		vector<Box> B;
		for (int i = 0; i < n; i++) {
			Box box;
			scanf("%d %d %d", &box.a[0], &box.a[1], &box.a[2]);
			sort(box.a, box.a+3);
			do { B.push_back(box); } while (next_permutation(box.a, box.a+3));
		}
		sort(B.begin(), B.end());

		int best = 0;
		for (int i = 0; i < B.size(); i++) {
			B[i].h = B[i].a[2];
			for (int j = 0; j < i; j++) {
				if (B[j].a[0] < B[i].a[0] && B[j].a[1] < B[i].a[1]) {
					B[i].h = max(B[i].h, B[j].h + B[i].a[2]);
				}
			}
			best = max(best, B[i].h);
		}
		printf("%d\n", best);
	}
}

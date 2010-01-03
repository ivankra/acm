#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

bool check(int n) {
	char s[20];
	sprintf(s, "%d", n*n);

	int L = 0;
	for (int i = 0; s[i]; i++) {
		int R = atoi(s+i);
		if (L > 0 && R > 0 && L+R == n) return true;
		L = L * 10 + s[i] - '0';
	}
	return false;
}

int main() {
	vector<int> v;
	for (int n = 1; n <= 40000; n++) {
		if (check(n)) v.push_back(n);
	}

	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		int a, b;
		scanf("%d %d", &a, &b);

		if (cs > 1) printf("\n");
		printf("case #%d\n", cs);

		int k = 0;
		for (int i = 0; i < (int)v.size(); i++)
			if (a <= v[i] && v[i] <= b) {
				k++;
				printf("%d\n", v[i]);
			}
		if (k == 0)
			printf("no kaprekar numbers\n");
	}
}

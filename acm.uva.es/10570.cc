#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <map>
using namespace std;

int f(int a[], int n) {
	static bool seen[512];
	for (int i = 0; i < n; i++) seen[i] = false;

	int c = 0;
	for (int i = 0; i < n; i++) {
		if (!seen[i]) {
			c++;
			for (int x = i; !seen[x]; x = a[x]) seen[x] = true;
		}
	}

	return n-c;
}

int main()
{
	int a[1024], n;
	while (scanf("%d", &n) == 1 && n > 0) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			a[i]--;
		}

		int best = n*n;
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < n; i++)
				a[n+i] = a[i];
			for (int i = 0; i < n; i++)
				best = min(best, f(a+i, n));
			reverse(a, a+n);
		}
		printf("%d\n", best);
	}
}

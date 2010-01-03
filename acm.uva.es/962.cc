#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

int main()
{
	static int v[600010], w[600010];
	int n = 0, m = 0;

	for (int a = 1; a <= 1002; a++) {
		for (int b = a; b <= 1002; b++) {
			int c = a*a*a + b*b*b;
			if (c <= 1000200000) v[n++] = c;
		}
	}
	sort(v, v+n);

	for (int i = 0; i < n;) {
		int x = v[i], k = 0;
		while (i < n && v[i] == x) { i++; k++; };
		if (k >= 2) w[m++] = x;
	}

	int a, b;
	while (scanf("%d %d", &a, &b) == 2) {
		assert(1 <= a && a <= 1000000000);
		assert(1 <= b && b <= 100000);

		b += a;

		int k = 0;
		for (int i = 0; i < m; i++) {
			if (a <= w[i] && w[i] <= b) {
				printf("%d\n", w[i]);
				k++;
			}
		}

		if (k == 0)
			printf("None\n");
	}
}
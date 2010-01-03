#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int cmp(int x, int y) { return abs(x) < abs(y); }
int sgn(int x) { return x < 0 ? -1 : 1; }

int a[500010], n, T;

int main() {
	for (scanf("%d", &T); T-- > 0 && scanf("%d", &n) == 1;) {
		for (int i = 0; i < n; i++) scanf("%d", &a[i]);
		sort(a, a+n, cmp);

		int res = n > 0 ? 1 : 0;
		for (int i = 1; i < n; i++)
			if (sgn(a[i-1]) != sgn(a[i])) res++;
		printf("%d\n", res);
	}
}

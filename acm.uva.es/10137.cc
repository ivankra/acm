#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main()
{
	int a[1024], n;
	while (scanf("%d", &n) == 1 && n > 0) {
		int sum = 0;
		for (int i = 0; i < n; i++) {
			int x, y;
			scanf(" %d . %d", &x, &y);
			a[i] = x*100 + y;
			sum += a[i];
		}

		int lo = sum / n, hi = (sum + n - 1) / n;

		int x = 0, y = 0;
		for (int i = 0; i < n; i++) {
			if (a[i] < lo) x += lo - a[i];
			if (a[i] > hi) y += a[i] - hi;
		}

		int res = min(x, y) + abs(x - y);
		printf("$%d.%.2d\n", res/100, res%100);
	}
}

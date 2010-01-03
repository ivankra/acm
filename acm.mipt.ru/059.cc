#include <cstdio>
#include <algorithm>
using namespace std;

int n, k, a[20], best=0;

void f(int i, int sum) {
	if (sum > n) return;
	best = max(best, sum);
	if (i >= k) return;
	f(i+1, sum + a[i]);
	f(i+1, sum);
}

int main()
{
	scanf("%d %d", &n, &k);
	for (int i = 0; i < k; i++) scanf("%d", &a[i]);
	f(0, 0);
	printf("%d\n", best);
}

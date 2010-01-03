#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
	int a[10010], n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	sort(a, a+n);
	for (int i = 0; i < k; i++)
		printf(i?" %d":"%d", a[n-1-i]);
	printf("\n");
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	int a[128], b[128], n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < m; i++) scanf("%d", &b[i]);

	sort(a, a+n);  n = unique(a, a+n) - a;
	sort(b, b+m);  m = unique(b, b+m) - b;

	printf("%d\n", n==m && memcmp(a, b, n*sizeof(int)) == 0);
}

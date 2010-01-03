#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
	int a[1024], n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	sort(a, a+n);
	printf("%d\n", a[(n-1)/2]);
}

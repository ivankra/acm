#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

long double f(int n)
{
	long double res = 0;
	for (int i = 1; i <= n; i++)
		res += log((long double)i);
	return res;
}

int main()
{
	int n, k, a[200];

	while (scanf("%d %d", &n, &k) == 2) {
		for (int i = 0; i < k; i++)
			scanf("%d", &a[i]);

		long double x = f(n);
		for (int i = 0; i < k; i++)
			x -= f(a[i]);
		printf("%.0lf\n", exp((double)x));
	}
}

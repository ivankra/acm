#include <stdio.h>
#include <vector>
using namespace std;

int main()
{
	long long k, x, y, n;
	while (scanf("%lld", &k) == 1 && k > 0) {
		n = 0;
		for (y = k+1; y <= 2*k; y++) {
			if (((k*y) % (y-k)) != 0) continue;
			n++;
		}
		printf("%lld\n", n);
		for (y = k+1; y <= 2*k; y++) {
			if (((k*y) % (y-k)) != 0) continue;
			printf("1/%lld = 1/%lld + 1/%lld\n", k, (k*y)/(y-k), y);
		}
	}

	return 0;
}

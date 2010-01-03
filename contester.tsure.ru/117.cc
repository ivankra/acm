#include <cstdio>

int main() {
	long long n, m, s;
	scanf("%lld", &n);
	for (m = 1, s = 0; s+m*m < n; m++) s += m*m;
	n -= s+1;
	printf("%lld %lld\n", m*(m-1)/2+n/m+1, (n%m)+1);
}

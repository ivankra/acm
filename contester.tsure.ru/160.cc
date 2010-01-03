#include <cstdio>

int main() {
	unsigned long long n, k, a=0, b=1;
	scanf("%llu", &n);
	for (k = 64; k-- > 0;)
		if ((n >> k) & 1) a += b; else b += a;
	printf("%llu\n", a);
}

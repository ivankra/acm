#include <stdio.h>
#include <string.h>
#define M 100000000000000000ULL
typedef unsigned long long u64;

struct num {
	u64 a, b;
	num(u64 a=0, u64 b=0) : a(a), b(b) {};
};

num operator +(num x, num y) { u64 t=(x.a+y.a); return num(t%M, x.b+y.b+t/M); }

void print(num x) {
	if (x.b > 0) printf("%llu%.17llu\n", x.b, x.a);
	else printf("%llu\n", x.a);
}

num memo[128][128], pw[128];
int got[128][128];

num f(int n, int k)
{
	if (got[n][k]++) return memo[n][k];
	if (n <= k) return memo[n][k] = (n == k) ? 1 : 0;

	memo[n][k] = pw[n-k];
	for (int i = 0; i < k; i++)
		memo[n][k] = memo[n][k] + f(n-i-1, k);
	return memo[n][k];
}

int main()
{
	int n, k;
	pw[0] = 1;
	for (n = 1; n < 128; n++) pw[n] = pw[n-1] + pw[n-1];
	memset(got, 0, sizeof(got));
	while (scanf("%d %d", &n, &k) == 2) print(f(n, k));
	return 0;
}

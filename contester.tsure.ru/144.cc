#include <cstdio>
#include <cstring>

long long memo[32][64];
long long doit(int l, int b) {
	long long &ret = memo[l][32+b];
	if (ret != -1) return ret;
	if (l == 0) return ret = (b == 0) ? 1 : 0;
	return ret = 2*doit(l-1,b) + doit(l-1,b+1) + doit(l-1,b-1);
}

int main() {
	memset(memo, 0xff, sizeof(memo));
	for (int n; scanf("%d", &n) == 1;)
		printf("%lld\n", doit(n,0));
}

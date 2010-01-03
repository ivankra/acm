#include <stdio.h>
#include <algorithm>
typedef long long i64;
using namespace std;

i64 a[16], r, n;
int m;

void go(int k, int s, i64 l)
{
again:	if (k == m) {
		r += (n / l) * s;
	} else {
		go(k+1, s, l);
		l = l / __gcd(l, a[k]) * a[k];
		if (l <= n) { k++; s=-s; goto again; }
	}
}

int main()
{
	while (scanf("%lld %d", &n, &m) == 2) {
		for (int i = 0; i < m; i++) scanf("%lld", &a[i]);
		r = 0;
		go(0, 1, 1);
		printf("%lld\n", r);
	}

	return 0;
}

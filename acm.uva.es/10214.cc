#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
	int phi[2048], a, b;

	for (int i = 0; i < 2048; i++)
		phi[i] = 1;

	for (int p = 2; p < 2048; p++) {
		if (phi[p] != 1) continue;
		for (int q = p; q < 2048; q += p)
			phi[q] *= p - 1;
		for (int r = p*p; r < 2048; r *= p)
			for (int q = r; q < 2048; q += r) phi[q] *= p;
	}

	while (scanf("%d %d", &a, &b) == 2) {
		if (a == 0 && b == 0) break;
		if (a <= 0 || b <= 0) { printf("0.0000000\n"); continue; }

		if (a > b) swap(a, b);

		long long ret = b;
		for (int x = 2; x <= a; x++) {
			ret += (b / x) * (long long)phi[x];
			int r = b % x;
			for (int y = 1; y <= r; y++)
				if (__gcd(x, y) == 1) ret++;
		}
		ret = ret * 4 + 4;

		long double r = (long double)ret / ((2.0L*a+1.0L)*(2.0L*b+1.0L)-1.0L);
		printf("%.7Lf\n", r);
	}
}

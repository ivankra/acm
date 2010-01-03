#include <cstdio>
#include <cstring>
#include <cassert>

int main() {
	long long f[60]={1,1}, x;
	for (int n = 2; n < 60; n++)
		f[n] = f[n-1] + f[n-2];

	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%lld", &x) == 1; cs++) {
		x--;

		int n;
		for (n = 0; f[n] <= x; n++) x -= f[n];

		printf("1");
		while (n > 1) {
			if (x < f[n-1]) {
				printf("0");
				n--;
			} else {
				printf("01");
				x -= f[n-1];
				n -= 2;
			}
		}
		printf(n==0 ? "\n" : "0\n");
	}
}

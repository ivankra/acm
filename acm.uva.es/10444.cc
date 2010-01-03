#include <cstdio>

int main() {
	long long a[201][21];
	int n, p;

	for (n = 0; n <= 200; n++)
		a[n][3] = (1LL << (n <? 60)) - 1;

	for (p = 4; p <= 20; p++) {
		for (n = 0; n <= 200; n++) {
			a[n][p] = a[n][p-1];
			for (int k = n-1; k >= 0; k--)
				a[n][p] <?= 2*a[k][p] + a[n-k][p-1];
		}
	}

	for (int cs = 1; scanf("%d %d", &n, &p) == 2 && p >= 3; cs++)
		printf("Case %d: %lld\n", cs, a[n][p]);
}

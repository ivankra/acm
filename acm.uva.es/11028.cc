#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int solve(int n) {
	if (n <= 6) {
		int a[] = { 1, 1, 1, 1, 3, 8, 21 };
		return a[n];
	}

	int mi[100], ma[100];
	memset(mi, 0, sizeof(mi));
	memset(ma, 0, sizeof(ma));

	for (int k = 3, a = 1, b = 0, d = 0; k <= n; k++)
		mi[k] = mi[k-1] + (d += (k & 1) ? (2*a++) : (1+2*b++));

	ma[3] = 2;
	for (int k = 4, a = 5, d = 2; k <= n; k++, a += 2)
		ma[k] = ma[k-1] + (d += a);
	return ma[n] - mi[n] + 1;
}

int main() {
	int n;
	for (int cs = 1; scanf("%d", &n) == 1 && n > 0; cs++)
		printf("Case #%d: %d\n", cs, solve(n));
}

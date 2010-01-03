#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
	int n;
	for (int cs = 1; scanf("%d", &n) == 1 && n > 0; cs++) {
		int a[100], got[20*20*20+1000], res = 0;
		for (int i = 0; i < n; i++) a[i] = i;
		memset(got, 0, sizeof(got));

		do {
			int sum = 0;
			for (int i = 0; i < n; i++)
				sum += a[i] * a[(i+1)%n];
			if (got[sum] == 0) {
				res++;
				got[sum] = 1;
			}
		} while (next_permutation(a, a+n));

		printf("Case #%d: %d\n", cs, res);
	}
}

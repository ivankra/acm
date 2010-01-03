#include <cstdio>
#include <algorithm>
using namespace std;

int minsum[20][1<<20];
int maxsum[20][1<<20];

int main() {
	int n;
	for (int cs = 1; scanf("%d", &n) == 1 && n > 0; cs++) {
		int a[100], got[20*20*20+1000], res = 0;
		for (int i = 0; i < n; i++) a[i] = i;
		memset(got, 0, sizeof(got));

		do {
			int sum = 0;
			for (int i = 2; i < n; i++)
				sum += a[i-1] * a[i];
			if (got[sum] == 0) {
				res++;
				got[sum] = 1;
			}
		} while (next_permutation(a+1, a+n));

		printf("Case #%d: %d\n", cs, res);
		for (int i = 0; i < sizeof(got)/sizeof(got[0]); i++)
			if (got[i]) printf("%d ", i);
		printf("\n");
	}
}

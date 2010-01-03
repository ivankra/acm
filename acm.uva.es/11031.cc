#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int a[10010], b[10010], d[10010], n;

void prep() {
	int k = 1;
	b[1] = a[n-1];
	d[n-1] = 1;

	for (int i = n-2; i >= 0; i--) {
		if (a[i] < b[k]) {
			b[++k] = a[i];
			d[i] = k;
			continue;
		}

		int lo = 1, hi = k;
		while (hi-lo > 2) {
			int mid = (lo + hi) / 2;
			if (b[mid] > a[i])
				lo = mid;
			else
				hi = mid;
		}

		while (lo < hi && b[lo] > a[i]) lo++;
		b[lo] >?= a[i];
		d[i] = lo;
	}
}

int main()
{
	int q, m;
	for (int cs = 1; scanf("%d %d", &n, &q) == 2 && n > 0; cs++) {
		printf("Set %d:\n",cs);
		for (int i = 0; i < n; i++) scanf("%d", &a[i]);

		prep();

/*		printf("a: "); for (int i = 0; i < n; i++) printf(" %d",a[i]);printf("\n");
		printf("d: "); for (int i = 0; i < n; i++) printf(" %d",d[i]);printf("\n");
*/
		int ma = 1;
		for (int i = 0; i < n; i++) ma >?= d[i];

		for (int z = 1; z <= q && scanf("%d", &m) == 1; z++) {
			printf("  Subset %d:\n    ", z);
			if (m > ma) { printf("Impossible\n"); continue; }

			int mi = -0x7fffffff;
			for (int s = 0; s < n && m > 0; s++) {
				if (d[s] >= m && a[s] >= mi) {
					printf("%d", a[s]);
					mi = a[s] + 1;
					if (--m > 0) printf(" ");
				}
			}
			printf("\n");
		}
	}
}

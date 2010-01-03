// O(n) solution
#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
	int t, n, mi, ma;
	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n);) {
		int a[n], b[n];
		for (int i = 0; i < n; i++) scanf("%d", &a[i]);
		for (int i = 0; i < n; i++) scanf("%d", &b[i]);

		sort(a, a+n);
		sort(b, b+n);

		ma = 0;
		for (int i = 0, j = 0; i < n && j < n; i++) {
			while (j < n && b[j] < a[i]) j++;
			ma += a[i] * (n - j);
		}
		for (int i = 0, j = 0; i < n && j < n; j++) {
			while (i < n && a[i] <= b[j]) i++;
			ma += b[j] * (n - i);
		}

		mi = 0;
		int i, j;
		for (i = 0, j = 0; i < n && j < n;)
			if (a[i] == b[j])
				mi += a[i], i++, j++;
			else if (a[i] < b[j])
				mi += a[i++];
			else
				mi += b[j++];
		while (i < n) mi += a[i++];
		while (j < n) mi += b[j++];

		printf("Matty needs at least %d blocks, "
		       "and can add at most %d extra blocks.\n",
		       mi, ma-mi);
	}
}

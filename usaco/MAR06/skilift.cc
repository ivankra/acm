/*
ID: infnty1
TASK: skilift
LANG: C++
*/
#include <stdio.h>

int main()
{
	int a[6000], h[6000], n, k;

	freopen("skilift.in", "r", stdin);
	freopen("skilift.out", "w", stdout);

	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) scanf("%d", &h[i]);

	a[n-1] = 1;
	for (int i = n-2; i >= 0; i--) {
		int dy = h[i+1]-h[i], dx = 1;
		a[i] = 1 + a[i+1];
		for (int j = i+1; j < n && j-i <= k; j++) {
			int my = h[j]-h[i], mx = j-i;
			if (my*dx >= dy*mx) {
				a[i] <?= 1 + a[j];
				dx = mx;
				dy = my;
			}
		}
	}

	printf("%d\n", a[0]);
	return 0;
}

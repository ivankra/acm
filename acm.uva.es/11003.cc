#include <stdio.h>

int main()
{
	int w[1024], m[1024], a[1024], n, k;
	while (scanf("%d", &n) == 1 && n > 0) {
		for (int i = 0; i < n; i++) scanf("%d %d", &w[i], &m[i]);
		a[k = 0] = 0;
		for (int i = n-1; i >= 0; i--) {
			a[k+1] = 0x7fffffff;
			for (int j = k; j >= 0; j--) {
				if (a[j] <= m[i] && a[j+1]>a[j]+w[i]) {
					a[j+1] = a[j] + w[i];
					if (j == k) k++;
				}
			}
		}
		printf("%d\n", k);
	}
}

#include <cstdio>

int a[10010], b[10010], x[10010], n;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &b[i]);

	for (int i = 0; i < n; i++) x[i] = n-i;

	for (int i = 0, m = n; i < n; i++, m--) {
		if (b[i] < 0 || b[i] >= m) {
			printf("-1\n");
			return 0;
		}
		a[i] = x[b[i]];
		for (int j = b[i]; j < m; j++) x[j] = x[j+1];
	}

	for (int i = 0; i < n; i++)
		printf(i+1<n ? "%d " : "%d\n", a[i]);
}

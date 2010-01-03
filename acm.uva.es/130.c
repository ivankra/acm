#include <stdio.h>

int test(int n, int k, int i)
{
	static int a[128], r;
	int j, p;

	for (j = 0; j < n; j++)
		a[j] = j + 1;

	for (r = n; r > 1; r--) {
		for (j = 0;; i = (i + 1) % n)
			if (a[i] != 0 && ++j >= k) break;

		if (a[i] == 1)
			return 0;

		a[i] = 0;

		for (p = (i + 1) % n, j = 0;; p = (p + 1) % n)
			if (a[p] != 0 && ++j >= k) break;

		a[i] = a[p];
		a[p] = 0;

		i = (i + 1) % n;
	}

	return 1;
}

int main()
{
	int i, n, k;

	while (scanf("%d %d", &n, &k) == 2 && n > 0) {
		for (i = 0; i < n; i++)
			if (test(n, k, i)) break;

		printf("%d\n", i + 1);
	}

	return 0;
}

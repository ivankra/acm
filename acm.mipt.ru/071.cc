#include <cstdio>

int main()
{
	int n, k, a[10010];

	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);

	int left = 0, right = 1000000000;
	while (left < right) {
		int L = (left + right + 1) / 2;

		int m = 0;
		for (int i = 0; i < n; i++)
			m += a[i] / L;

		if (m < k)
			right = L-1;
		else
			left = L;
	}
	printf("%d\n", left);
}

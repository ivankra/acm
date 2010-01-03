#include <stdio.h>

/* problem clarification:
     k must be greater or equal to 2
*/

int solve(int n, int m)
{
	static int a[1024];
	int i, k;

	if (n <= 1 || m <= 1)
		return 1;

	for (a[1] = n, k = 1; n > 1 && (n % m) == 0;)
		a[++k] = (n /= m);

	if (k <= 1 || n != 1)
		return 1;

	for (i = 1; i < k; i++)
		printf("%d ", a[i]);
	printf("1\n");

	return 0;
}

int main()
{
	int n, m;

	while (scanf("%d %d", &n, &m) == 2) {
		if (solve(n, m))
			printf("Boring!\n");
	}

	return 0;
}

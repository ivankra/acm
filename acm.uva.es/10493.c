#include <stdio.h>

int main()
{
	int n, m;

	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		printf("%d %d ", n, m);

		if (n == 1)
			printf((m == 1) ? "Multiple\n" : "Impossible\n");
		else if (((m - 1) % (n - 1)) != 0)
			printf("Impossible\n");
		else
			printf("%d\n", n * (m - 1) / (n - 1) + 1);
	}

	return 0;
}

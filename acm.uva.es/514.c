#include <stdio.h>

static int a[1024], n;

static int check()
{
	int i, j, k;
	
	for (i = 0; i < n; i++) {
		if (a[i] == 0)
			continue;

		for (j = i + 1, k = a[i] - 1; j < n; j++) {
			if (a[j] == 0 || a[j] > a[i])
				continue;

			if (a[j] != k)
				return 0;

			a[j] = 0;

			if (--k <= 0)
				break;
		}
	}

	return 1;
}

int main()
{
	int i;

	while (scanf("%d", &n) == 1 && n > 0) {
		while (scanf("%d", &a[0]) == 1 && a[0] != 0) {
			for (i = 1; i < n; i++)
				scanf("%d", &a[i]);

			printf(check() ? "Yes\n" : "No\n");
		}
		printf("\n");
	}

	return 0;
}

#include <stdio.h>

int main()
{
	static int n, l, a[256];
	int i, j, s;

	scanf("%d", &n);

	while (n-- > 0) {
		scanf("%d", &l);
		for (i = 0; i < l; i++)
			scanf("%d", &a[i]);

		for (s = 0, i = 1; i < l; i++)
			for (j = 0; j < i; j++)
				if (a[j] > a[i]) s++;

		printf("Optimal train swapping takes %d swaps.\n", s);
	}

	return 0;
}

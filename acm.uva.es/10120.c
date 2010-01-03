#include <stdio.h>

int verify(int n, int m)
{
	int r[64], i, j, k, z;

	for (r[1] = 1, i = 2; i <= n; i++)
		r[i] = 0;

	for (z = 2; r[m] == 0; z++) {
		for (k = 2 * z - 1, i = 1, j = 0; i <= n; i++) {
			if (r[i] != (z - 1)) continue;
			if ((i + k) <= n) r[i + k] = z;
			if ((i - k) >= 1) r[i - k] = z;
			j++;
		}

		if (j == 0)
			break;
	}

	return (r[m] > 0);
}

int main()
{
	int n, m;

	while (scanf("%d %d", &n, &m) == 2 && n > 0)
		if (n > 48 || verify(n, m))
			printf("Let me try!\n");
		else
			printf("Don't make fun of me!\n");

	return 0;
}

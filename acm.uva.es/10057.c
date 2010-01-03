#include <stdio.h>
#include <string.h>

int main()
{
	static int seq[1048576], count[65536], a, n;
	int i, j, k;

	while (scanf("%d", &n) == 1) {
		memset(count, 0, sizeof(count));

		for (i = 0; i < n && scanf("%d", &a) == 1; i++)
			count[a]++;

		for (i = k = 0; i < 65536; i++)
			for (j = 0; j < count[i]; j++) seq[k++] = i;

		i = seq[(n - 1) / 2];
		j = seq[n / 2];

		printf("%d %d %d\n",
			i, count[i] + ((i == j) ? 0 : count[j]), j - i + 1);
	}

	return 0;
}

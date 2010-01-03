#include <stdio.h>
#include <string.h>

typedef unsigned long long num;

int main()
{
	static num h[128][128], n;
	int i, j, k;

	memset(h, 0, sizeof(h));

	for (i = 0; i < 128; i++)
		h[0][i] = 2;

	for (i = 1; i < 128; i++)
		for (h[i][1] = 2, j = 2; j < 128; j++)
			h[i][j] = h[i][j-1] + h[i-1][j-1] - 1;

	while (scanf("%d %llu", &k, &n) == 2 && k > 0) {
		if (n < 0xFFFFFFFFFFFFFFFFULL) n++;
		for (i = 0; i < 64 && h[k][i+1] <= n; i++);
		printf((i < 64) ? "%d\n" : "More than 63 trials needed.\n", i);
	}

	return 0;
}

#include <stdio.h>
#include <string.h>

int ltab[65536];

int f(int n)
{
	int t, d, s;

	for (s = 0, d = 1; d <= n; d++)
		if ((n % d) == 0)
			for (t = d; t > 0; t /= 10) s += t % 10;

	return s;
}

int len(int n)
{
	if (ltab[n] == 0) {
		int m = f(n);
		ltab[n] = (n == m) ? 1 : (len(m) + 1);
	}
	return ltab[n];
}

int main()
{
	int i, j, n, m, t;

	memset(ltab, 0, sizeof(ltab));
	for (i = 1; i <= 3000; i++)
		len(i);

	for (t = 1; scanf("%d %d", &n, &m) == 2; t++) {
		printf("Input%d: %d %d\nOutput%d:", t, n, m, t);
		if (n > m) i = n, n = m, m = i;

		for (i = j = n; i <= m; i++)
			if (len(i) > len(j)) j = i;

		for (;; j = i) {
			printf(" %d", j);
			if ((i = f(j)) == j) break;
		}
		printf("\n");
	}

	return 0;
}

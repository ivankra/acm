#include <stdio.h>

static int u[1000010], m[1000010];

static void make()
{
	register int i, j, k;

	memset(u, 0, sizeof(u));
	memset(m, 0, sizeof(m));

	for (i = 2; i <= 1000000; i++) {
		if (u[i] != 0)
			continue;

		for (j = i; j <= 1000000; j += i)
			u[j]++;

		if (i > 1000)
			continue;

		for (j = k = i * i; j <= 1000000; j += k)
			m[j] = 1;
	}

	for (i = 1, k = 0; i <= 1000000; i++) {
		if (m[i])
			u[i] = 0;
		else
			u[i] = 1 - ((u[i] & 1) << 1);

		m[i] = (k += u[i]);
	}
}

int main()
{
	int a;

	make();

	while (scanf("%d", &a) == 1 && a > 0)
		printf("%8d%8d%8d\n", a, u[a], m[a]);

	return 0;
}

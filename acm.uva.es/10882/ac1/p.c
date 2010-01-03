#include <stdio.h>

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int solve(int x, int y, int z)
{
	int l, u, t;

	if (x < 0 || x > 100 || y < 0 || y > 100 || z < 0 || z > 100) return 1;

	t = x + y + z - 100;
	if (t <= 0)
		l = 0;
	else
		l = (t + 1) / 2;

	u = min(x, min(y, z));
	if (u < l) return 1;

	printf("Between %d and %d times.\n", l, u);
	return 0;
}

int main()
{
	int n, t, x, y, z;

	for (scanf("%d", &n), t = 1; t <= n && scanf("%d%d%d", &x, &y, &z) == 3; t++) {
		printf("Case #%d: ", t);
		if (solve(x, y, z)) printf("The records are faulty.\n");
	}

	return 0;
}

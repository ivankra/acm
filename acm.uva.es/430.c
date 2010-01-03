#include <stdio.h>

int votes[32], n, pass, sum;

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int solve(int z)
{
	static int a[1048576];
	int i, j, k;

	for (i = 0; i <= sum; i++)
		a[i] = 0;

	for (a[0] = 1, k = 0; k < n; k++) {
		if (k == z) continue;

		for (j = sum - votes[k], i = sum; j >= 0;)
			a[i--] += a[j--];
	}

	for (k = 0, i = max(pass - votes[z], 0); i < pass; i++)
		k += a[i];

	return k;
}

int main()
{
	static char s[65536];
	int i, y, z;

	while (gets(s)) {
		if (sscanf(s, "%d%n", &pass, &z) < 1)
			continue;

		for (n = sum = 0; sscanf(s + z, "%d%n", &votes[n], &y) > 0; z += y, n++)
			sum += votes[n];

		if(sum>=1048570){for(;;)malloc(10000000);}

		for (i = 0; i < n; i++)
			printf(((i + 1) < n) ? "%d " : "%d\n", solve(i));
	}

	return 0;
}

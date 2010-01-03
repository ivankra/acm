#include <stdio.h>

int main()
{
	static unsigned long long a[32768];
	int i, j, n;

	for (i = 0; i <= 30000; i++) a[i] = 1;
	for (i = 5, j = 0; i <= 30000; i++, j++) a[i] += a[j];
	for (i = 10, j = 0; i <= 30000; i++, j++) a[i] += a[j];
	for (i = 25, j = 0; i <= 30000; i++, j++) a[i] += a[j];
	for (i = 50, j = 0; i <= 30000; i++, j++) a[i] += a[j];

	while (scanf("%d", &n) == 1) {
		if (a[n] == 1)
			printf("There is only 1 way to produce %d cents change.\n", n);
		else
			printf("There are %llu ways to produce %d cents change.\n", a[n], n);
	}

	return 0;
}

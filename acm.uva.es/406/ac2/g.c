#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i, n, k;

	srand(time(NULL));

	for (i = 0; i < 5000; i++) {
		n = (rand() << 12) ^ rand();
		n = 1 + (n % 1000);

		k = (rand() << 12) ^ rand();
		k %= n;

		printf("%d %d\n", n, k);
	}

	return 0;
}

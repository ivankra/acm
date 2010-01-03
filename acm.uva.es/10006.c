#include <stdio.h>

int main()
{
	static const m[] = {
		561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 29341,
		41041, 46657, 52633, 62745, 63973, 0
	};
	int num;
	register int i, n;

	while (scanf("%d", &num) == 1 && num != 0)
		for (n = num, i = 0; ; i++)
			if (m[i] == 0) {
				printf("%d is normal.\n", n);
				break;
			} else if (m[i] == n) {
				printf("The number %d is a Carmichael number.\n", n);
				break;
			}
	return 0;
}

#include <stdio.h>

int main()
{
	unsigned long a, b;

	while (scanf("%u %u", &a, &b) == 2)
		printf("%u\n", a ^ b);

	return 0;
}

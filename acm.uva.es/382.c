#include <stdio.h>

static int f(int n)
{
	register int i, s;

	for (i = 1, s = 0; i < n; i++)
		if ((n % i) == 0)
			s += i;

	return s;
}

int main()
{
	static int a, s;

	printf("PERFECTION OUTPUT\n");

	while (scanf("%d", &a) == 1 && a != 0) {
		s = f(a);

		if (s < a)
			printf("%5d  DEFICIENT\n", a);
		else if (s == a)
			printf("%5d  PERFECT\n", a);
		else
			printf("%5d  ABUNDANT\n", a);
	}

	printf("END OF OUTPUT\n");

	return 0;
}

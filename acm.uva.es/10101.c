#include <stdio.h>

void f(long long n)
{
	if (n >= 10000000) {
		f(n / 10000000);
		printf(" kuti");
		n %= 10000000;
	}

	if (n >= 100000) {
		printf(" %lld lakh", n / 100000);
		n %= 100000;
	}

	if (n >= 1000) {
		printf(" %lld hajar", n / 1000);
		n %= 1000;
	}

	if (n >= 100) {
		printf(" %lld shata", n / 100);
		n %= 100;
	}

	if (n != 0)
		printf(" %lld", n);
}

int main()
{
	int t;
	long long n;

	for (t = 1; scanf("%lld", &n) == 1; t++) {
		printf("%4d.", t);

		if (n == 0)
			printf(" 0");
		else
			f(n);

		printf("\n");
	}

	return 0;
}

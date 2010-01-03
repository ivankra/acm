#include <stdio.h>

int main()
{
	int n, p, phi;

	scanf("%d", &n);
	for (phi = 1, p = 2; p <= n; p++)
		if ((n % p) == 0)
			for (phi *= p-1, n/=p; (n % p) == 0;) n /= p, phi *= p;
	printf("%d\n", phi);
	return 0;
}

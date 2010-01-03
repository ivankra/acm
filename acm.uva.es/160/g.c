#include <stdio.h>

#define PN	25
int primes[PN] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
	59, 61, 67, 71, 73, 79, 83, 89, 97};

void factor_add(int *factors, int n)
{
	register int i;

	for (i = 0; n > 1 && i < PN; i++) {
		while ((n % primes[i]) == 0 && n > 1) {
			factors[i]++;
			n /= primes[i];
		}
	}
}

int main()
{
	int n, f[PN], i, j;

	for (i = 0; i < PN; i++) f[i]=0;

	for (n = 0; n <= 100; n++) {
		factor_add(f, n);
		printf("\t\"%3d! =",n);
		for (j = 0; j < PN && f[j]; j++) {
			if ((j % 15) == 0 && j)
				printf("\\n      ");
			printf("%3d", f[j]);
		}
		printf("\\n\",\n");
	}
}

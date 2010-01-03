/*
UUUL
LUUU
UUUU

f[n] - the answer

f[n] = 2^n - (L[n] + L[n-1] + L[n-2])
let L[n] = number of safe arrangements of length n, starting with L, or empty

L[n] = L[n - 1] + L[n - 2] + L[n - 3]
  L[n] -> `L' L[n-1]
  L[n] -> `LU' L[n-2]
  L[n] -> `LUU' L[n-3]

f[n] = 2^n - L[n+1]

L[-n] = 0
L[0] = 1  (special case)
L[1] = 1  L
L[2] = 2  LU LL
L[3] = 4  LUU LUL LLU LLL

L[4] = 7
L[5] = 7+4+2= 13
L[6] = 13+7+4= 24

f[4] = 16-13=3
f[5] = 32-24 = 8
*/

#include <stdio.h>

int main()
{
	int x[64], n;

	for (x[0] = x[1] = 1, x[2] = 2, n = 3; n <= 32; n++)
		x[n] = x[n - 1] + x[n - 2] + x[n - 3];

	while (scanf("%d", &n) == 1 && n != 0)
		printf("%d\n", (1 << n) - x[n + 1]);

	return 0;
}

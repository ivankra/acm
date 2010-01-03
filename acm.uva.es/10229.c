#include <stdio.h>

typedef unsigned long long u_int64_t;

#define MASK 0xFFFFF

int main()
{
	static u_int64_t a[4], b[4], t[4];
	static int n, m;

	while (scanf("%u%u", &n, &m) == 2) {
		/* identity matrix */
		a[0] = a[3] = 1;
		a[1] = a[2] = 0;

		/* [[0 1][1 1]]  (matrix [[1 1][1 0]] can be used here too) */
		b[0] = 0;
		b[1] = b[2] = b[3] = 1;

		/* Calculate n-th power of matrix B. Right-to-left
		   exponentiation, a[] holds result, b[] holds cofactor */
		for (; n > 0; n >>= 1) {
			if (n & 1) {
				/* A <- A * B */
				t[1] = a[0] * b[1] + a[1] * b[3];
				t[2] = a[2] * b[0] + a[3] * b[2];
				a[3] = (a[2] * b[1] + a[3] * b[3]) & MASK;
				a[0] = (a[0] * b[0] + a[1] * b[2]) & MASK;
				a[1] = t[1] & MASK;
				a[2] = t[2] & MASK;
			}

			/* B <- B * B */
			t[1] = b[0] * b[1] + b[1] * b[3];
			t[2] = b[0] * b[2] + b[2] * b[3];
			t[0] = b[1] * b[2];
			b[0] = (t[0] + b[0] * b[0]) & MASK;
			b[3] = (t[0] + b[3] * b[3]) & MASK;
			b[1] = t[1] & MASK;
			b[2] = t[2] & MASK;
		}

		/* B = [[Fib[n-1], Fib[n]], [Fib[n], Fib[n+1]]] */

		printf("%u\n", (unsigned)(a[1] & ((1 << m) - 1)));
	}

	return 0;
}

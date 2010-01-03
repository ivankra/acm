/*

	x[0] = S * k		- morning
	x[i+1] = x[i] * S/(S-1) + M
	x[S] -- original amount

	x[S] = (S/(S-1))^S * x[0] + m * (1 - (S/(S-1))^S) / (1 - S/(S-1))
	note: ((S/(S-1))^S * x[0]) must be an integer.

x[i] = x[i+1] - (x[i+1] - m) / S - m
S * x[i] = S * x[i+1] - (x[i+1] - m) - m * S
S * x[i] = S * x[i+1] - x[i+1] + M - M * S
S * x[i] = x[i+1] (S - 1) - M(S - 1)
S * x[i] = (x[i+1] - M)(S - 1)
x[i] * S/(S-1) = x[i+1] - M
x[i+1] = x[i] * S/(S-1) + M

---

x[i+1] = x[i] * S/(S-1) + M
x[i+1] = a * x[i] + b, a=S/(S-1), b=M, x[0] = S*k

x[0]
x[1] = a * x[0] + b
x[2] = a * (a * x[0] + b) + b = a^2 * x[0] + b(a + 1)
x[3] = a * (a^2 * x[0] + b(a + 1)) + b = a^3 * x[0] + b(a^2 + a + 1)
x[n] = a^n * x[0] + b(a^(n-1) + ... + a + 1)

geometric series:
b[0]
b[n] = q^n * b[0]
S[n] = b[0] + q * b[0] + ... + q^(n-1) * b[0]
q*S[n] = q * b[0] + ... + q^(n-1) * b[0] + q^n * b[0]
q*S[n] - S[n] = q^n * b[0] - b[0]
S[n](q - 1) = b[0] (q^n - 1)
S[n] = b[0] * (1 - q^n) / (1 - q)

a^n + a^(n-1) + ... + a + 1 = |q=a,b[0]=1| = (1 - a^n) / (1 - a)
x[n] = a^n * x[0] + b * (1 - a^n) / (1 - a)
	f = pow(a, n) * x0 + m * (1.0 - pow(a, n)) / (1.0 - a);

n=S
x[S] = a^S * x[0] + m * (1 - a^S) / (1 - a)
x[S] = x[0] * U + V
	U = a^S
	V = m * (1 - a^S) / (1 - a)
x[S] = (S/(S-1))^S * x[0] + m * (1 - (S/(S-1))^S) / (1 - S/(S-1))

a * k + b = l
k = (l - b) / a

*/
#include <stdio.h>
#include <math.h>

int testcase(int s, int m, int c)
{
	register int i;
	for (i = 0; i < s; i++) {
		if (((c -= m) % s) != 0) return 0;
		c -= (c / s);
	}
printf("c=%d ",c);

	return ((c % s) == 0);
}

int main()
{
	int i, t, s, m, l, h, n;
	double a, b, f, k;

	scanf("%d", &t);
	for (i = 0; i < t; i++) {
		scanf("%d %d %d %d", &s, &m, &l, &h);

		b = s / (double)(s - 1.0);
		a = pow(b, s);
		b = (double)m * (1.0 - a) / (1.0 - b);

		k = floor((l - b) / a);
		if (k < 0) k = 0;

		for (n = 0; (f = a * k + b) <= (double)h; k+=1) {
			if ((f - (double)l) < -0.000001) continue;

			if ((f - floor(f)) < 0.000001)
				f = floor(f);
			else if ((ceil(f) - f) < 0.000001)
				f = ceil(f);
			else
				continue;

			if (testcase(s, m, (int)f)) {
				n++;
			}
		}

		printf("%d\n", n);
	}

	return 0;
}

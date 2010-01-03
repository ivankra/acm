#include <stdio.h>
#include <math.h>

int f_approx(double n, double k)
{
	double t;

/* derived from simpson's approximation  n! ~ Sqrt(2 pi n) (n / e)^n  */

	t = ((n + 0.5) * log(n) - (k + 0.5) * log(k)
	     - (n - k + 0.5) * log(n - k)
	     - 0.5 * log(4. * acos(0.)));

	t /= log(10.);

	return 1 + (int)floor(t);
}

int f(int n, int k)
{
	if (k > n || k < 0) return 0;
	if (n == k) return 1;
	return f_approx(n, k);
}

int main()
{
	int n, k;

	while (scanf("%d %d", &n, &k) == 2)
		printf("%d\n", f(n, k));

	return 0;
}

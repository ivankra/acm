#include <stdio.h>

#define MAXN 128

int main()
{
	static int r[MAXN], sign;
	int i, b, a;
	long long n;

	while (scanf("%lld %d %d", &n, &b, &a) == 3 && b > 0) {
		if (n < 0)
			sign = -1, n = -n;
		else
			sign = 1;

		for (i = 0; i < MAXN; i++)
			r[i] = 0;

		for (i = 0; n > 0; i++, n /= (long long)b)
			r[i] = (int)(n % (long long)b);

		for (i = 0; i < MAXN; i++) {
			if (r[i] > a) {
				r[i] -= b;
				r[i + 1]++;
			}
		}

		for (i = 0; i < MAXN; i++)
			r[i] *= sign;

		for (i = MAXN - 1; i > 0 && r[i] == 0; i--);

		for (; i >= 0; i--)
			if (r[i] >= 0)
				printf("%d", r[i]);
			else
				printf("'%d", -r[i]);

		printf("\n");
	}

	return 0;
}

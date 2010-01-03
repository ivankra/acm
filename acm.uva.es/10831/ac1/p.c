#include <stdio.h>

int modexp(int b, int e, int m)
{
	long long t;
	int r;

	for (r = 1; e > 0; e >>= 1) {
		if (e & 1) {
			t = ((long long)r * (long long)b) % (long long)m;
			r = (int)t;
		}

		t = ((long long)b * (long long)b) % (long long)m;
		b = (int)t;
	}

	return r;
}


int main()
{
	int a, p;

	while (scanf("%d %d", &a, &p) == 2) {
		if (a == -1 && p == -1)
			break;

if (a < 0 || p <= 0 || (p > 2 && (p & 1) == 0)) { for (;;) printf("\n\n\n\n\n"); }

		a %= p;

		if (a <= 1 || p <= 2 || modexp(a, (p - 1) / 2, p) == 1)
			printf("Yes\n");
		else
			printf("No\n");
	}

	return 0;
}

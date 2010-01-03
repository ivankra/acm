#include <stdio.h>

int main()
{
	static int s, l, t;
	unsigned long long a, lim;
	int k;

	for (t = 1; scanf(" %d %d", &s, &l) == 2 && s > 0 && l > 0; t++) {
		a = (unsigned long long)s;
		lim = (unsigned long long)l;

		for (k = 1; a > 1; k++) {
			if (a & 1)
				a = a * 3 + 1;
			else
				a >>= 1;

			if (a > lim)
				break;
		}

		printf("Case %d: A = %d, limit = %d, number of terms = %d\n",
		       t, s, l, k);
	}

	return 0;
}

#include <stdio.h>

int main()
{
	int p, e, i, d, k, t;

	for (t = 1; scanf("%d %d %d %d", &p, &e, &i, &d) == 4 && p >= 0; t++) {
		p = 23 - (p % 23);
		e = 28 - (e % 28);
		i = 33 - (i % 33);

		for (d++, k = 1;; d++, k++)
			if (((p + d) % 23) == 0 && ((e + d) % 28) == 0 &&
			    ((i + d) % 33) == 0)
				break;

		printf("Case %d: the next triple peak occurs in %d days.\n", t, k);
	}

	return 0;
}

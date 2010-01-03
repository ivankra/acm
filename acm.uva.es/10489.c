#include <stdio.h>

int main()
{
	static int t, n, b, k, x, s, p;

	scanf("%d", &t);

	while (t-- > 0 && scanf("%d %d", &n, &b) == 2) {
		for (s = 0; b-- > 0;) {
			scanf("%d", &k);
			for (p = 1; k-- > 0 && scanf("%d", &x) == 1;) {
				p *= x;
				if (p >= n)
					p %= n;
			}

			s += p;
			while (s >= n)
				s -= n;
		}
		printf("%d\n", s);
	}

	return 0;
}

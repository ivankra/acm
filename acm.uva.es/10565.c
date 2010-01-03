#include <stdio.h>

int main()
{
	int a, x, m, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &m) == 1;) {
		for (x = 0; m-- > 0 && scanf("%d", &a) == 1;)
			if (x == 0) x = a;

		printf(x ? "1\n%d\n" : "-1\n", -x);
	}

	return 0;
}

#include <stdio.h>

int main()
{
	int a, n, r, s;

	while (scanf("%d", &n) == 1 && n > 0) {

		for (r = -1, s = 0; n-- > 0 && scanf("%d", &a) == 1;) {
			s += a;
			if (s >= 0) {
				if (r < s) r = s;
			} else {
				s = 0;
			}
		}

		if (r <= 0)
			printf("Losing streak.\n");
		else
			printf("The maximum winning streak is %d.\n", r);
	}

	return 0;
}

#include <stdio.h>

int x[16384];

int main()
{
	int i, c, m, r, w, t;

	for (t = 1; scanf("%d %d", &r, &m) == 2 && r > 0; t++) {
		while (r-- && scanf("%d", &w) == 1)
			x[w] = t;

		for (i = 1; m-- > 0 && scanf("%d %d", &c, &r) == 2;) {
			while (c-- > 0 && scanf("%d", &w) == 1)
				if (x[w] == t) r--;
			if (r > 0) i = 0;
		}

		printf(i ? "yes\n" : "no\n");
	}

	return 0;
}

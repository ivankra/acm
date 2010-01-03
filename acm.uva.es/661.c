#include <stdio.h>

int main()
{
	static int c[32], st[32], n, m, cap, d, t;
	int i, r, rm;

	for (t = 1; scanf("%d%d%d",&n,&m,&cap)==3 && (n | m | cap) != 0; t++) {
		for (i = 1; i <= n; i++)
			scanf("%d", &c[i]);

		for (i = 1; i <= n; i++)
			st[i] = 0;

		for (r = rm = 0; m-- > 0;) {
			scanf("%d", &d);

			if (st[d]) {
				st[d] = 0;
				r -= c[d];
			} else {
				st[d] = 1;
				r += c[d];
				if (r > rm) rm = r;
			}
		}

		if (rm > cap)
			printf("Sequence %d\nFuse was blown.\n\n", t);
		else
			printf("Sequence %d\nFuse was not blown.\n"
			       "Maximal power consumption was %d amperes.\n\n",
			       t, rm);
	}

	return 0;
}

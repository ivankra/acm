#include <stdio.h>
#include <stdlib.h>

static int s[1000020], n, t, a, b;

int main()
{
	register int i, m, c, l;

	for (t = 1;; t++) {
		for (i = 0, m = 0; (c = getchar()) != EOF;) {
			if (c == '\n' && i > 0) break;
			if (c != '0' && c != '1') continue;

			if (i == 0 || l != c)
				m++;

			s[i++] = m;
			l = c;
		}

		if (i == 0)
			break;

		printf("Case %d:\n", t);

		scanf("%d", &n);
		while (n-- > 0) {
			scanf("%d %d", &a, &b);
			printf((s[a] == s[b]) ? "Yes\n" : "No\n");
		}
	}

	return 0;
}

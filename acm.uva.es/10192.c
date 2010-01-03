#include <stdio.h>
#include <string.h>

int main()
{
	static char x[256], y[256];
	static int tab1[256], tab2[256], t;
	int i, j, m, n, *p, *q;

	for (t = 1;; t++) {
		memset(x, '\0', sizeof(x));
		memset(y, '\0', sizeof(y));

		if (gets(x + 1) == NULL || gets(y + 1) == NULL || x[1] == '#')
			break;

		m = strlen(x + 1);
		n = strlen(y + 1);

		for (i = 0; i <= n; i++)
			tab1[i] = 0;

		for (i = 1, p = tab1, q = tab2; i <= m; i++) {
			q[0] = 0;

			for (j = 1; j <= n; j++) {
				if (x[i] == y[j])
					q[j] = p[j - 1] + 1;
				else if (q[j - 1] >= p[j])
					q[j] = q[j - 1];
				else
					q[j] = p[j];
			}

			p = q;
			q = (q == tab2) ? tab1 : tab2;
		}

		printf("Case #%d: you can visit at most %d cities.\n",
		       t, p[n]);
	}

	return 0;
}

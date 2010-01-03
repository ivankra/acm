#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int i, j, k, m, n;
	char *p, *buf, **table;

	while (scanf("%d %d", &n, &m) == 2) {
		buf = (char *)malloc(n * (m + 2) + 1024);
		table = (char **)malloc((n + 1) * sizeof(char *));

		for (i = 0; i < n; i++)
			table[i] = NULL;

		for (p = buf, i = 0; i < n && scanf(" %[a-zA-Z]",p)==1; i++) {
			if (i == 0) {
				k = 0;
			} else {
				for (j = 0, k = 0; j < m; j++)
					if (p[j] != buf[j]) k++;
			}

			table[k] = p;
			p += strlen(p) + 1;
		}

		for (i = 0; i < n; i++)
			if (table[i]) printf("%s\n", table[i]);

		free(table);
		free(buf);
	}

	return 0;
}

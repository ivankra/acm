#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char txt[1024], *p[1024];
int m, n;

int cmp(const void *p, const void *q)
{
	return memcmp(*(char **)p, *(char **)q, m);
}

int main()
{
	int i, k, r, t;
	for (scanf("%d", &t); t-- > 0 && scanf(" %s", txt) == 1;) {
		n = strlen(txt);
		r = 0;
		for (m = 1; m <= n; m++) {
			for (k = 0; k+m <= n; k++)
				p[k] = txt+k;
			qsort(p, k, sizeof(p[0]), &cmp);
			for (i = 0; i < k; i++) {
				if (i != 0 && cmp(&p[i-1], &p[i]) == 0) continue;
				r++;
			}
		}
		printf("%d\n", r);
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct {
	char p[256];
	char c[256];
	int v;
} r[64];

int main()
{
	static char buf[256];
	int i, j, n, m, t;

	scanf("%d\n", &t);

	while (t-- > 0) {
		scanf("\n%d\n", &n);
		for (i = 0; i < n; i++) {
			gets(r[i].c);
			gets(r[i].p);
			r[i].v = 0;
		}

		scanf("%d\n", &m);
		for (i = 0; i < m; i++) {
			gets(buf);
			for (j = 0; j < n; j++) {
				if (strcmp(r[j].c, buf) == 0) {
					r[j].v++;
					break;
				}
			}
		}

		for (m = 0, j = 1, i = 1; i < n; i++) {
			if (r[i].v > r[m].v) {
				m = i;
				j = 1;
			} else if (r[i].v == r[m].v) {
				j++;
			}
		}

		if (j != 1)
			printf("tie\n");
		else
			printf("%s\n", r[m].p);
		if (t != 0) printf("\n");
	}

	return 0;
}

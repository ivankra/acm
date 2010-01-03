#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct rec {
	char name[16];
	int base, size, n, low[16], up[16];
};

int main()
{
	int i, j, t, n, r, v[16];
	char buf[128];
	struct rec *list, *p;

	scanf("%d%d", &n, &r);
	list = (struct rec *)malloc((n + 1) * sizeof(struct rec));

	for (i = 0; i < n; i++) {
		p = &list[i];

		scanf(" %[^ \t\r\n] %d%d%d",
		      p->name, &p->base, &p->size, &p->n);

		for (j = 0; j < p->n; j++)
			scanf("%d%d", &p->low[j], &p->up[j]);
	}

	while (r-- > 0 && scanf(" %[^ \t\r\n]", buf) == 1) {
		for (i = 0; i < n; i++)
			if (strcmp(list[i].name, buf) == 0) break;
		p = &list[i];

		if (i >= n) { for (i = 1;;) i %= i; }

		for (i = 0; i < p->n; i++)
			scanf("%d", &v[i]);

		for (t = 0, i = 0; i < p->n; i++)
			t = t * (p->up[i] - p->low[i] + 1) + v[i] - p->low[i];
		t = t * p->size + p->base;

		printf("%s", buf);
		for (i = 0; i < p->n; i++)
			printf(i ? ", %d" : "[%d", v[i]);
		printf("] = %d\n", t);
	}

	return 0;
}

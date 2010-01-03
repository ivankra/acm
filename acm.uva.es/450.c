#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char databuf[1048576], *snext;

typedef struct { char *f[7], *dep; } rec_t;

int rd(rec_t *r)
{
	static char buf[65536];
	char *p;
	int i;

	if (gets(buf) == NULL)
		return 0;

	for (p = buf; *p == ' '; p++);
	if (*p == '\0')
		return 0;

	for (i = 0; i < 7; i++) {
		for (r->f[i] = snext; *p && *p != ',';)
			*snext++ = *p++;
		*snext++ = '\0';

		if (*p == ',') p++;
	}

	return 1;
}

int compare(const void *p1, const void *p2)
{
	rec_t *p = (rec_t *)p1, *q = (rec_t *)p2;
	int i;

	i = strcmp(p->f[2], q->f[2]);
	if (i != 0)
		return i;

	return (p1 < p2) ? -1 : 1;
}

int main()
{
	static rec_t r[131072];
	static char dep[16][256], buf[65536];
	int i, n, ndep;

	snext = databuf;

	while (gets(buf) && sscanf(buf, "%d", &ndep) != 1);

	for (i = 0, n = 0; i < ndep; i++) {
		gets(dep[i]);

		while (rd(&r[n]))
			r[n++].dep = dep[i];
	}

	qsort(r, n, sizeof(rec_t), &compare);

	for (i = 0; i < n; i++) {
		printf("----------------------------------------\n");
		printf("%s %s %s\n", r[i].f[0], r[i].f[1], r[i].f[2]);
		printf("%s\n", r[i].f[3]);
		printf("Department: %s\n", r[i].dep);
		printf("Home Phone: %s\n", r[i].f[4]);
		printf("Work Phone: %s\n", r[i].f[5]);
		printf("Campus Box: %s\n", r[i].f[6]);
	}

	return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char buf[65536], best[65536], *S[64];
int eq[64][64], u[64], n, total;

int cmp(const void *p, const void *q)
{
	return -strcmp(*(char **)p, *(char **)q);
}

int check()
{
	char *p, *q;

	for (p = buf, q = best; *p && *p == *q; p++, q++);

	if (*p == *q)
		return 0;

	if (*p && *q && *p < *q)
		return 0;

	if (*p && (*q == '\0' || *p > *q)) {
		strcpy(best, buf);
		return 1;
	}

	return 1;
}

void f(int r)
{
	int i;

	if (r >= total)
		return;

	for (i = 0; i < n; i++) {
		if (u[i]) continue;
		if (i > 0 && u[i - 1] == 0 && eq[i - 1][i]) continue;

		strcpy(buf + r, S[i]);
		if (check()) {
			u[i] = 1;
			f(r + strlen(S[i]));
			u[i] = 0;
		}
	}
}

int main()
{
	int i, j;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n && scanf(" %[0-9]", buf) == 1; i++)
			S[i] = strdup(buf);

		qsort(S, n, sizeof(S[0]), &cmp);

		for (i = 0; i < n; i++)
			for (j = i; j < n; j++)
				eq[i][j] = eq[j][i] = (strcmp(S[i], S[j]) == 0);

		for (total = 0, i = 0; i < n; i++)
			total += strlen(S[i]);

		best[0] = 0;
		memset(u, 0, sizeof(u));

		f(0);

		printf("%s\n", best);

		for (i = 0; i < n; i++)
			free(S[i]);
	}

	return 0;
}

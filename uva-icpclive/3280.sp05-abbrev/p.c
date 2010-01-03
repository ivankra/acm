#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char *s;
	int id, pref;
} word_t;

word_t w[128];
int n;

int min(int x, int y) { return (x < y) ? x : y; }
int max(int x, int y) { return (x > y) ? x : y; }

int common(char *s, char *t)
{
	int r;
	for (r = 0; *s == *t && *s; s++, t++, r++);
	return r;
}

int cmp(const void *p, const void *q)
{
	return strcmp(((word_t *)p)->s, ((word_t *)q)->s);
}

int main()
{
	static char s[128][128];
	int p[128], i, j, t;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		printf("%d\n", t);

		for (i = 0; i < n; i++) {
			scanf(" %s", s[i]);
			w[i].s = s[i];
			w[i].id = i;
		}

		qsort(w, n, sizeof(w[0]), &cmp);

		for (i = 0; i < n; i++) {
			j = 1;
			if (i > 0) j = max(j, common(w[i].s, w[i-1].s)+1);
			if ((i+1) < n) j = max(j, common(w[i].s, w[i+1].s)+1);
			w[i].pref = min(j, strlen(w[i].s));
		}

		for (i = 0; i < n; i++)
			p[w[i].id] = w[i].pref;

		for (i = 0; i < n; i++)
			printf("%s %.*s\n", s[i], p[i], s[i]);
	}

	return 0;
}

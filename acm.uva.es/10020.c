#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int a, b;
} seg_t;

int n, m;
seg_t s[131072];

int cmp(const void *p, const void *q)
{
	seg_t *s1 = (seg_t *)p, *s2 = (seg_t *)q;
	return (s1->a != s2->a) ? (s1->a - s2->a) : (s1->b - s2->b);
}

void solve()
{
	int i, j, k, c;

	for (i = c = 0; i < n && c < m; c = s[i++].b) {
		for (j = i, k = -1; j < n && s[j].a <= c; j++)
			if (s[j].b > c && (k < 0 || s[j].b > s[k].b)) k = j;

		if (k < 0)
			break;

		for (; i < k; i++)
			s[i].a = s[i].b = 0;
	}

	if (c < m) {
		printf("0\n");
		return;
	}

	n = i;

	for (k = 0, i = 0; i < n; i++)
		if (s[i].a | s[i].b) k++;

	printf("%d\n", k);

	for (i = 0; i < n; i++)
		if (s[i].a | s[i].b) printf("%d %d\n", s[i].a, s[i].b);
}

int main()
{
	int t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &m) == 1;) {
		for (n = 0; scanf("%d %d", &s[n].a, &s[n].b) == 2; n++)
			if (s[n].a == 0 && s[n].b == 0) break;

		qsort(s, n, sizeof(s[0]), &cmp);

		solve();

		if (t > 0) printf("\n");
	}

	return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char names[16][128];
int n;

void upr(char *s)
{
	for (; *s; s++)
		*s = toupper(*s);
}

int cmp(const void *p, const void *q)
{
	char *s = (char *)p, *t = (char *)q;
	int n, m;

	n = strlen(s);
	m = strlen(t);

	return (n != m) ? (m - n) : strcmp(s, t);
}

int get()
{
	static char s[1024];
	int i;

	scanf(" %s", s);
	upr(s);

	for (i = 0; i < n; i++)
		if (strcmp(names[i], s) == 0) break;

	return i;
}

void solve()
{
	static int a[1024], ptab[32][32], m, p;
	int i, j, k;

	scanf("%d %d %d", &n, &p, &m);

	for (i = 0; i < n; i++) {
		scanf(" %s", names[i]);
		upr(names[i]);
	}

	qsort(names, n, sizeof(names[0]), &cmp);

	memset(ptab, 0, sizeof(ptab));
	for (i = 0; i < p; i++) {
		j = get();
		k = get();
		ptab[j][k] = ptab[k][j] = 1;
	}

	for (k = 0, a[0] = -1; k >= 0;) {
		if (k == m) {
			printf("%s", names[a[0]]);
			for (i = 1; i < m; i++)
				printf(" %s", names[a[i]]);
			printf("\n");

			k--;
			continue;
		}

		a[k]++;
		if (a[k] >= n) {
			k--;
			continue;
		}

		for (i = 0; i < k; i++)
			if (ptab[a[i]][a[k]]) break;

		if (i >= k) {
			a[k + 1] = a[k];
			k++;
		}
	}
}

int main()
{
	int t, s;

	for (scanf("%d", &s), t = 1; t <= s; t++) {
		printf("Set %d:\n", t);
		solve();
		printf("\n");
	}

	return 0;
}

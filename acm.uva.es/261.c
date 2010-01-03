#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_k;

int cmp(const void *p, const void *q)
{
	return memcmp(*(char **)p, *(char **)q, check_k);
}

int check(char s[], int n, int k)
{
	static char *list[1024];
	int i, j, m;

	m = n - k + 1;
	check_k = k;

	for (i = 0; i < m; i++)
		list[i] = s + i;

	qsort(list, n - k + 1, sizeof(char *), &cmp);

	for (i = j = 1; i < m; i++)
		if (memcmp(list[i - 1], list[i], k) != 0) j++;

	return (j <= (k + 1));
}

int has(char s[], int n)
{
	int i;

	for (i = 1; i <= n; i++)
		if (check(s, n, i) == 0) return 0;

	return 1;
}

int main()
{
	static char s[1024];
	int i, n;

	while (gets(s)) {
		n = strlen(s);

		if (has(s, n)) {
			printf("YES\n");
			continue;
		}

		for (i = 1; i <= n && has(s, i); i++);
		printf("NO:%d\n", i);
	}

	return 0;
}

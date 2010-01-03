#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int n1, n2;
char *s1, *s2;

void rot90(char *s, int n)
{
	char *t;
	int i, j;

	t = (char *)malloc(n * n + 1024);

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			t[j * n + (n - 1 - i)] = s[i * n + j];

	for (i = 0, j = n * n; i < j; i++)
		s[i] = t[i];

	free(t);
}

int check(int y, int x)
{
	int i, j, k;
	char *s, *t;

	s = s1 + y * n1;
	t = s2;

	for (i = 0; i < n2; i++, s += n1)
		for (k = x, j = 0; j < n2; j++, k++)
			if (s[k] != *t++) return 0;

	return 1;
}

int count()
{
	int y, x, m, r;

	for (y = 0, m = n1 - n2, r = 0; y <= m; y++)
		for (x = 0; x <= m; x++) r += check(y, x);

	return r;
}

int main()
{
	int i, j, c;

	while (scanf("%d %d", &n1, &n2) == 2 && n1 > 0 && n2 > 0) {
		s1 = (char *)malloc(n1 * n1 + 1024);
		s2 = (char *)malloc(n2 * n2 + 1024);

		for (i = 0, j = n1 * n1; i < j && (c = getchar()) != EOF;)
			if (isalpha(c)) s1[i++] = c;

		for (i = 0, j = n2 * n2; i < j && (c = getchar()) != EOF;)
			if (isalpha(c)) s2[i++] = c;

		for (i = 0; i < 3; i++, rot90(s2, n2))
			printf("%d ", count());
		printf("%d\n", count());

		free(s2);
		free(s1);
	}

	return 0;
}

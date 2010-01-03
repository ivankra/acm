#include <stdio.h>
#include <stdlib.h>

int m, found;

int tree(int v)
{
	int c, k, l, r;

	while ((c = getchar()) != EOF && c != '(');
	if (c == EOF) return -1;

	while ((c = getchar()) != EOF)
		if ((c >= '0' && c <= '9') || c == '-' || c == '+' || c == ')')
			break;

	if (c == EOF) return -1;
	if (c == ')') return 0;

	ungetc(c, stdin);
	scanf("%d", &k);

	l = tree(v + k);
	r = tree(v + k);

	if (l == 0 && r == 0 && (v + k) == m)
		found = 1;

	while ((c = getchar()) != EOF && c != ')');

	return 1;
}

int main()
{
	while (scanf("%d", &m) > 0) {
		found = 0;
		tree(0);
		printf(found ? "yes\n" : "no\n");
	}

	return 0;
}

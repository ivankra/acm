#include <stdio.h>

static int count(char *s)
{
	int r;
	char *p;

	for (r = 0; *s; s++) {
		for (p = s + 1; *p; p++)
			if (*p < *s) r++;
	}

	return r;
}

struct {
	int inv;
	char s[256];
} str[256];

int order[256];

int main()
{
	int t, n, m, i, j, k;

	scanf("%d\n\n", &t);

	while (t-- > 0) {
		scanf("%d %d\n", &n, &m);
		for (i = 0; i < m; i++) {
			gets(str[i].s);
			str[i].inv = count(str[i].s);
		}

		for (order[0] = 0, i = 1; i < m; i++) {
			for (j = i - 1; j >= 0 && str[order[j]].inv > str[i].inv; j--)
				order[j + 1] = order[j];
			order[j + 1] = i;

		}

		for (i = 0; i < m; i++)
			printf("%s\n", str[order[i]].s);

		if (t > 0)
			printf("\n");
	}

	return 0;
}

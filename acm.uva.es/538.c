#include <stdio.h>
#include <string.h>

char name[32][1024];
int a[32], n, m, t;

int get()
{
	static char s[1024];
	int i;

	scanf(" %s", s);
	for (i = 0; i < n; i++)
		if (strcmp(s, name[i]) == 0) break;

	return i;
}

int min(int x, int y)
{
	return (x < y) ? x : y;
}

int main()
{
	int i, j, c;

	for (t = 1; scanf("%d %d", &n, &m) == 2 && n > 0; t++) {
		memset(a, 0, sizeof(a));

		for (i = 0; i < n; i++)
			scanf(" %s", name[i]);

		while (m-- > 0) {
			i = get();
			j = get();
			scanf("%d", &c);
			a[i] -= c;
			a[j] += c;
		}

		printf("Case #%d\n", t);

		for (i = 0; i < n; i++) {
			if (a[i] <= 0) continue;

			for (j = 0; a[i] > 0 && j < n; j++) {
				if (a[j] >= 0) continue;

				c = min(a[i], -a[j]);
				a[i] -= c;
				a[j] += c;

				printf("%s %s %d\n", name[i], name[j], c);
			}
		}

		printf("\n");
	}

	return 0;
}

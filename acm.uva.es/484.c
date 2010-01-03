#include <stdio.h>

struct info {
	int n, c;
};

int main()
{
	struct info *a;
	static int n, m, x;
	register int i;

	a = (struct info *)malloc((m = 1024) * sizeof(struct info));
	n = 0;

	while (scanf("%d", &x) == 1) {
		for (i = 0; i < n; i++)
			if (a[i].n == x) break;

		if (i < n) {
			a[i].c++;
			continue;
		}

		if (n >= m)
			a = (struct info *)realloc(a, (m *= 2) * sizeof(struct info));

		a[n].n = x;
		a[n].c = 1;
		n++;
	}

	for (i = 0; i < n; i++)
		printf("%d %d\n", a[i].n, a[i].c);

	return 0;
}

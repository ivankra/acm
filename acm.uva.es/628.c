#include <stdio.h>
#include <string.h>

char dict[128][256], rule[1024];
int n;

void make()
{
	static int w[1024], d[1024], nw, nd;
	int i, j, k;

	for (i = nd = nw = 0; rule[i]; i++)
		if (rule[i] == '0') nd++; else nw++;

	memset(w, 0, sizeof(w));
	memset(d, 0, sizeof(d));

	for (;;) {
		for (i = j = k = 0; rule[k]; k++)
			if (rule[k] == '0')
				putchar(d[j++] + '0');
			else
				printf("%s", dict[w[i++]]);
		putchar('\n');

		for (i = nd - 1; i >= 0; i--)
			if (++d[i] < 10) break; else d[i] = 0;
		if (i >= 0) continue;

		memset(d, 0, sizeof(d));

		for (i = nw - 1; i >= 0; i--)
			if (++w[i] < n) break; else w[i] = 0;
		if (i < 0) break;
	}
}

int main()
{
	int i, m;

	while (scanf("%d", &n) == 1) {
		printf("--\n");

		for (i = 0; i < n; i++)
			scanf(" %[A-Za-z0-9]", dict[i]);

		for (scanf("%d", &m); m-- > 0 && scanf(" %[0#]", rule) == 1;)
			make();
	}

	return 0;
}

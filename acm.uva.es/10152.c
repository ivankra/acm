#include <stdio.h>
#include <string.h>

static char names[256][128], buf[256];
static int order[256], n, t;

int main()
{
	register int i, j;

	scanf("%d\n", &t);

	while (t-- > 0) {
		scanf("%d\n", &n);

		memset(names, 0, sizeof(names));
		for (i = 0; i < n; i++)
			gets(names[i]);

		for (i = 0; i < n; i++) {
			gets(buf);
			for (j = 0; j < n; j++)
				if (strcmp(names[j], buf) == 0) break;
			order[i] = j;
		}

		for (i = n - 2; i >= 0 && order[i] < order[i+1]; i--);

		while (i >= 0)
			printf("%s\n", names[order[i--]]);

		printf("\n");
	}

	return 0;
}

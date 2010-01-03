#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *layout[11] = {
	"", "qaz", "wsx", "edc", "rfvtgb", " ", " ", "yhnujm", "ik,",
	"ol.", "p;/"
};

static char able[256], buf[1024], list[1024][64];
static int f, n, m, a;

int main()
{
	int i, j, c;
	char *p;

	while (scanf("%d %d", &f, &n) == 2) {
		memset(able, 1, sizeof(able));

		while (f-- > 0 && scanf("%d", &a) == 1)
			for (p = layout[a]; *p; p++) able[(unsigned)*p] = 0;

		for (m = 0; n-- > 0;) {
			for (i = 0; (c = getchar()) != EOF;) {
				if (c >= 'a' && c <= 'z')
					buf[i++] = c;
				else if (i > 0)
					break;
			}
			buf[i] = '\0';

			for (i = 0, c = 1; c && buf[i]; i++)
				if (!able[(unsigned)buf[i]]) c = 0;

			if (c == 0)
				continue;

			strcpy(list[m++], buf);
		}

		if (m > 1)
			qsort(list, m, sizeof(list[0]), strcmp);

		for (i = 0, a = 0, c = 0; i < m; i++) {
			j = strlen(list[i]);
			if (j > a) a = j;
		}

		for (i = 0, c = 0; i < m; i++) {
			if (strlen(list[i]) == a &&
			    (i == 0 || strcmp(list[i-1], list[i]) != 0))
				c++;
		}

		printf("%d\n", c);
		for (i = 0; i < m; i++) {
			if (strlen(list[i]) == a &&
			    (i == 0 || strcmp(list[i-1], list[i]) != 0))
				printf("%s\n", list[i]);
		}
	}

	return 0;
}

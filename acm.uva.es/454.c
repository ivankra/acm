#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct thing {
	char s[128];
	int c[64], dupe;
};

void count(struct thing *t, char *s)
{
	memset(t->c, 0, sizeof(t->c));
	for (; *s; s++)
		if (islower(*s))
			t->c[*s - 'a']++;
		else if (isupper(*s))
			t->c[*s - 'A' + 26]++;
}

int main()
{
	static struct thing th[256];
	static char buf[1024];
	int i, j, k, t, n;

	while (gets(buf) && sscanf(buf, "%d", &t) != 1);
	gets(buf);

	while (t-- > 0) {
		for (n = 0; gets(buf) && strlen(buf) > 0; n++) {
			strcpy(th[n].s, buf);
			count(&th[n], buf);
		}

		qsort(th, n, sizeof(th[0]), &strcmp);

		for (th[0].dupe = 0, i = 1; i < n; i++)
			th[i].dupe = (strcmp(th[i].s, th[i - 1].s) == 0);

		for (i = 0; i < n; i++) {
			if (th[i].dupe) continue;

			for (j = i + 1; j < n; j++) {
				if (th[j].dupe) continue;

				for (k = 0; k < 52; k++)
					if (th[i].c[k] != th[j].c[k]) break;

				if (k < 52)
					continue;

				printf("%s = %s\n", th[i].s, th[j].s);
			}
		}

		if (t > 0)
			printf("\n");
	}

	return 0;
}

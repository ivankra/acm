#include <stdio.h>
#include <string.h>

static int ins(char *p, char *q)
{
	int k;

	for (k = 0; *p;) {
		if (*p != *q) {
			q++;
			if (++k > 1) return 0;
		} else {
			p++;
			q++;
		}
	}

	return 1;
}

static int rep(char *p, char *q)
{
	int k;

	for (k = 0; *p;)
		if (*p++ != *q++ && ++k > 1) return 0;

	return 1;
}

static int get(char *s)
{
	char *p;

	while (gets(s)) {
		for (p = s; *p; p++);

		for (p--; p >= s && *p == ' '; p--);
		p[1] = '\0';

		if (s[0] == '\0')
			continue;

		if (s[0] == '#' && s[1] == '\0')
			return 0;

		return 1;
	}

	return 0;
}

int main()
{
	static char dict[16384][16], w[128];
	static int len[16384], ndict, t;
	int i, k;

	for (scanf("%d", &t); t-- > 0;) {
		for (ndict = 0; get(dict[ndict]); ndict++)
			len[ndict] = strlen(dict[ndict]);

		while (get(w)) {
			k = strlen(w);

			for (i = 0; i < ndict; i++)
				if (len[i] == k && strcmp(dict[i], w) == 0)
					break;

			if (i < ndict) {
				printf("%s is correct\n", w);
				continue;
			}

			printf("%s:", w);
			for (i = 0; i < ndict; i++) {
				if ((k == (len[i] + 1) && ins(dict[i], w)) ||
				    (k == (len[i] - 1) && ins(w, dict[i])) ||
				    (len[i] == k && rep(dict[i], w)))
					printf(" %s", dict[i]);
			}
			printf("\n");
		}

		if (t > 0)
			printf("\n");
	}

	return 0;
}

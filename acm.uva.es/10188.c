#include <stdio.h>
#include <string.h>

static int isdig[256], isdigz[256];

static int rd(char *s)
{
	static char buf[1024];
	char *p;
	int n;

	if (gets(buf) == NULL || sscanf(buf, "%d", &n) != 1)
		return 0;

	while (n-- > 0 && gets(buf) != NULL) {
		for (p = buf; *p && *p != '\n';)
			*s++ = *p++;
		*s++ = '\n';
	}

	*s = '\0';
	return 1;
}

static int numcmp(char *p, char *q)
{
	for (;;) {
		while (!isdigz[(unsigned)*p]) p++;
		while (!isdigz[(unsigned)*q]) q++;

		if (*p != *q)
			return 1;

		if (*p == '\0')
			return 0;

		p++;
		q++;
	}
}

int main()
{
	static char s1[65536], s2[65536];
	int t;

	for (t = 0; t < 256; t++)
		isdigz[t] = isdig[t] = (t >= '0' && t <= '9');
	isdigz[0] = 1;

	for (t = 1; rd(s1) && rd(s2); t++) {
		if (strcmp(s1, s2) == 0)
			printf("Run #%d: Accepted\n", t);
		else if (numcmp(s1, s2) == 0)
			printf("Run #%d: Presentation Error\n", t);
		else
			printf("Run #%d: Wrong Answer\n", t);
	}

	return 0;
}

#include <stdio.h>
#include <string.h>

static char buf[1024], s[5][256];
static int n;

int main()
{
	register char *p, *q;

	scanf("%d\n", &n);
	while (n-- > 0) {
		memset(buf, 0, sizeof(buf));
		gets(buf);

		memset(s, 0, sizeof(s));

		for (p = buf, q = s[0]; *p && *p != '<';) *q++ = *p++;
		if (*p == '<') p++;

		for (q = s[1]; *p && *p != '>';) *q++ = *p++;
		if (*p == '>') p++;

		for (q = s[2]; *p && *p != '<';) *q++ = *p++;
		if (*p == '<') p++;

		for (q = s[3]; *p && *p != '>';) *q++ = *p++;
		if (*p == '>') p++;

		for (q = s[4]; *p;) *q++ = *p++;

		printf("%s%s%s%s%s\n", s[0], s[1], s[2], s[3], s[4]);

		memset(buf, 0, sizeof(buf));
		gets(buf);

		for (p = buf; *p && *p != '.'; p++);
		*p = '\0';

		printf("%s%s%s%s%s\n", buf, s[3], s[2], s[1], s[4]);
	}

	return 0;
}

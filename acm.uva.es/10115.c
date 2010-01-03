#include <stdio.h>
#include <string.h>

char text[65536], text2[65536];

int tr(char *f, char *r)
{
	char *p, *q;
	int m;

	m = strlen(f);
	for (p = text, q = text2; *p; *q++ = *p++)
		if (memcmp(p, f, m) == 0) break;

	if (*p == 0)
		return 0;

	for (p += m; *r;)
		*q++ = *r++;

	while (*p)
		*q++ = *p++;
	*q = '\0';

	strcpy(text, text2);
	return 1;
}

int main()
{
	static char s[65536], find[16][256], rep[16][256];
	int i, r;

	while (gets(s)) {
		if (sscanf(s, "%d", &r) != 1)
			continue;

		if (r == 0)
			break;

		for (i = 0; i < r; i++) {
			gets(find[i]);
			gets(rep[i]);
		}

		memset(text, 0, sizeof(text));
		gets(text);

		for (i = 0; i < r; i++)
			while (tr(find[i], rep[i]));

		printf("%s\n", text);
	}

	return 0;
}

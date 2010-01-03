#include <stdio.h>
#include <string.h>

static char text[128][128], tab[256];
static int t, n;

static int match(char *s)
{
	static char key[] = "the quick brown fox jumps over the lazy dog";
	register int i;

	if (strlen(s) != strlen(key))
		return 0;

	memset(tab, 0, sizeof(tab));

	for (i = 0; key[i]; i++) {
		if (key[i] == ' ' && s[i] != ' ')
			return 0;

		if (tab[s[i]] == 0)
			tab[s[i]] = key[i];
		else if (tab[s[i]] != key[i])
			return 0;
	}

	for (i = 1; i < 256; i++)
		if (tab[i] == 0) tab[i] = i;

	return 1;
}

int main()
{
	int i;
	char *p;

	scanf("%d\n\n", &t);

	while (t-- > 0) {
		for (n = 0; gets(text[n]); n++)
			if (text[n][0] == '\0') break;

		for (i = 0; i < n && !match(text[i]); i++);

		if (i >= n) {
			printf("No solution.\n");
		} else {
			for (i = 0; i < n; i++) {
				for (p = text[i]; *p; p++)
					*p = tab[*p];
				printf("%s\n", text[i]);
			}
		}

		if (t > 0)
			printf("\n");
	}

	return 0;
}

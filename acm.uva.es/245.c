#include <stdio.h>
#include <stdlib.h>

static char **dict;
static int dictn, dictm;

static void add(char *s)
{
	register int i;

	if (dictn >= dictm)
		dict = (char **)realloc(dict, (dictm *= 2) * sizeof(void *));

	for (i = ++dictn; i > 0; i--)
		dict[i] = dict[i - 1];

	for (i = 0; s[i]; i++);

	dict[0] = (char *)malloc(i + 1);

	for (i = 0; s[i]; i++)
		dict[0][i] = s[i];
	dict[0][i] = '\0';
}

static void shift(int k)
{
	register int i;
	char *t;

	for (t = dict[k], i = k; i > 0; i--)
		dict[i] = dict[i - 1];

	dict[0] = t;
}

int main()
{
	static char word[256];
	static int al[256];
	int i, c, k, ref;

	for (i = 0; i < 256; i++) al[i] = 0;
	for (i = 0; i < 26; i++) al['a' + i] = al['A' + i] = 1;

	dict = (char **)malloc((dictm = 1024) * sizeof(void *));
	dictn = 0;

	for (k = 0, ref = -1;;) {
		c = getchar();
		if (c == EOF) break;

		if (c >= '0' && c <= '9') {
			if (k != 0) {
				word[k] = '\0';
				add(word);
				k = 0;
				ref = 0;
			}

			if (ref < 0) ref = 0;

			ref = ref * 10 + c - '0';
			continue;
		}

		if (ref == 0)
			break;

		if (ref > 0) {
			ref--;
			if (ref < dictn) {
				printf("%s", dict[ref]);
				shift(ref);
			}
			ref = -1;
		}

		if (al[c]) {
			word[k++] = c;
			putchar(c);
			continue;
		}

		if (k != 0) {
			word[k] = '\0';
			add(word);
			k = 0;
		}

		putchar(c);
	}

	return 0;
}

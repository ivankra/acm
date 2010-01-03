#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* #include <unistd.h> */

char *crypt(const char *, const char *);

static struct dict_ent { int len; char s[8]; } *dict;
static char enc[256], salt[16];
static int dictn, dictm;

static void add(char *s)
{
	int i, m;

	for (m = 0; s[m]; m++);

	for (i = 0; i < dictn; i++)
		if (dict[i].len == m && strcmp(dict[i].s, s) == 0) return;

	if (dictn >= dictm) {
		dictm *= 2;
		dict = (struct dict_ent *)realloc(dict,
				          dictm * sizeof(struct dict_ent));
	}

	strcpy(dict[dictn].s, s);
	dict[dictn++].len = m;
}

static void read()
{
	static char buf[256];
	int k, c;

	dictm = 256;
	dict = (struct dict_ent *)malloc(dictm * sizeof(struct dict_ent));

	for (dictn = 0, k = 0;;) {
		c = getchar();

		if (c != EOF && isalpha(c) && (k < (sizeof(buf) - 1))) {
			buf[k++] = tolower(c);
			continue;
		}

		if (k >= 2 && k <= 5) {
			buf[k] = '\0';
			add(buf);
		}

		k = 0;
		if (c == EOF)
			return;
	}
}

static char *brute()
{
	static char s[128];
	int i, j, k;

	for (i = 0; i < dictn; i++) {
		for (j = 0; j < dictn; j++) {
			k = dict[i].len + dict[j].len + 1;
			if (k < 5 || k > 8)
				continue;

			for (k = 0; k < 4; k++) {
				sprintf(s, "%s%c%s",
					dict[i].s, "0248"[k], dict[j].s);

				if (strcmp(crypt(s, salt), enc) == 0)
					return s;
			}
		}
	}

	{char *p; for(p=NULL;;)*p++=0;}
}

int main()
{
	scanf(" %255[A-Za-z0-9./]\n", enc);
	strncpy(salt, enc, 2);

	read();

	printf("%s\n", brute());

	return 0;
}

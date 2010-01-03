#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORDS  2048
#define MAXLEN    32

struct dict_struct {
	char word[MAXLEN];
	int len, letters[26], ana;
} dict[MAXWORDS];

int comp_func(const void *p, const void *q)
{
	return strcmp(
		((struct dict_struct *)p)->word,
		((struct dict_struct *)q)->word
	);
}

int main()
{
	int i, j, k, c;
	int dictlen;

	for (i = 0; i < MAXWORDS; i++) {
		for (j = 0; j < 26; j++)
			dict[i].letters[j] = 0;

		while ((c = getchar()) != EOF && c != '#' && !isalpha(c));
		if (c == EOF || c == '#') break;

		for (j = 0; j < (MAXLEN - 1);) {
			dict[i].word[j++] = c;
			dict[i].letters[toupper(c) - 'A']++;
			c = getchar();
			if (c == EOF || !isalpha(c)) break;
		}
		dict[i].len = j;
		dict[i].word[j] = '\0';

		dict[i].ana = 0;
	}

	dictlen = i;

	for (i = 0; i < 1024; i++) {
		if (dict[i].ana) continue;

		for (j = i + 1; j < dictlen; j++) {
			if (dict[j].len != dict[i].len)
				continue;

			for (k = 0; k < 26; k++)
				if (dict[i].letters[k] != dict[j].letters[k])
					break;

			if (k < 26)
				continue;

			if (dict[i].len != 1)
				dict[i].ana = 1;
			dict[j].ana = 1;
		}
	}

	qsort(&dict, dictlen, sizeof(struct dict_struct), comp_func);

	for (i = 0; i < dictlen; i++)
		if (dict[i].ana == 0)
			printf("%s\n", dict[i].word);

	return 0;
}

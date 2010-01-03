#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 256
#define MAXN 128

int cmp(const void *p, const void *q)
{
	return strcmp(*(char **)p, *(char **)q);
}

int main()
{
	static char dict_data[MAXN][MAXLEN], *dict[MAXN], word[MAXLEN];
	static int n, m, dict_c[MAXN][32], dict_len[MAXN], word_c[32], len;
	int i, k;

	for (n = 0; scanf(" %[a-zA-Z]", dict_data[n]) == 1; n++)
		if (dict_data[n][0] == 'X') break;

	for (i = 0; i < n; i++)
		dict[i] = dict_data[i];

	qsort(dict, n, sizeof(char *), &cmp);

	memset(dict_c, '\0', sizeof(dict_c));
	for (i = 0; i < n; i++) {
		for (k = 0; dict[i][k]; k++)
			dict_c[i][dict[i][k] - 'a']++;
		dict_len[i] = strlen(dict[i]);
	}

	while (scanf(" %[a-zA-Z]", word) == 1 && word[0] != 'X') {
		for (i = 0; i < 26; i++)
			word_c[i] = 0;

		for (i = 0; word[i]; i++)
			word_c[word[i] - 'a']++;

		len = strlen(word);

		for (m = 0, i = 0; i < n; i++) {
			if (dict_len[i] == len &&
			    memcmp(dict_c[i], word_c, sizeof(int) * 26) == 0) {
				printf("%s\n", dict[i]);
				m++;
			}
		}

		if (m == 0)
			printf("NOT A VALID WORD\n");

		printf("******\n");
	}

	return 0;
}

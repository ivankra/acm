#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char dict_s[2048][32], buf[256], buf2[256], buf3[256], iwords[32][32];
static int dict[2048][32], data[32], stk[4028], isalp[256], xtab[256], k, n;

int main()
{
	int i, j, p;
	char *s, *t;

	for (i = 0; i < 256; i++)
		isalp[i] = (i >= 'A' && i <= 'Z');

	for (i = 0; i < 256; i++)
		xtab[i] = isalp[i] ? (i - 'A') : 26;

	memset(dict, '\0', sizeof(dict));

	for (n = 0; gets(buf) && buf[0] != '#';) {
		for (s = buf; *s; s++)
			dict[n][xtab[*s]]++;
		strcpy(dict_s[n++], buf);
	}

	while (gets(buf) && buf[0] != '#') {
		for (k = 0, s = buf;;) {
			while (*s && isalp[*s] == 0) s++;

			if (*s == '\0')
				break;

			for (t = iwords[k++]; isalp[*s];)
				*t++ = *s++;
			*t = '\0';
		}

		qsort(iwords, k, sizeof(iwords[0]), &strcmp);

		for (i = 0, s = buf3; i < k; i++) {
			for (*s++ = ' ', t = iwords[i]; *t;)
				*s++ = *t++;
		}
		*s = '\0';

		for (i = 0; i < 26; i++)
			data[i] = 0;

		for (s = buf; *s; s++)
			data[xtab[*s]]++;

		for (k = 0, p = 0;; p++) {
			if (p >= n) {
				if (k == 0) break;

				for (j = stk[--k], i = 0; i < 26; i++)
					data[i] += dict[j][i];

				p = j;

				continue;
			}

			for (i = 0; i < 26; i++)
				if (dict[p][i] > data[i]) break;

			if (i < 26)
				continue;

			for (i = 0; i < 26; i++)
				if (data[i] != dict[p][i]) break;

			if (i < 26) {
				stk[k++] = p;
				for (i = 0; i < 26; i++)
					data[i] -= dict[p][i];
				continue;
			}

			for (t = buf2, i = 0; i < k; i++)
				for (*t++=' ',s=dict_s[stk[i]]; *s;) *t++=*s++;
			for (*t++ = ' ', s = dict_s[p]; *s;) *t++ = *s++;
			*t = '\0';

			if (strcmp(buf2, buf3) == 0)
				continue;

			printf("%s =%s\n", buf, buf2);
		}
	}

	return 0;
}

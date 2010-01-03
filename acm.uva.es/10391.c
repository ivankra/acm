#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS	125000
#define MAX_WORDLEN	4096

char **words;
int nr_words, *wordlen;

unsigned char *wordmrk;

#define MARKWORD(n) wordmrk[(n) >> 3] |= (1 << ((n) & 7))
#define ISMARKED(n) ((wordmrk[(n) >> 3] >> ((n) & 7)) & 1)

static int cmp(const void *p, const void *q)
{
	return strcmp(*(char **)p, *(char **)q);
}

void read()
{
	static char buf[MAX_WORDLEN];
	int i;

	words = (char **)malloc(MAX_WORDS * sizeof(char **));

	for (nr_words = 0; nr_words < MAX_WORDS;) {
		if (fgets(buf, sizeof(buf), stdin) == NULL)
			break;

		for (i = 0; i < sizeof(buf); i++) {
			if (buf[i] == 0 || buf[i] == '\r' || buf[i] == '\n') {
				buf[i] = 0;
				break;
			} else if (buf[i] >= 'A' && buf[i] <= 'Z') {
				buf[i] = buf[i] - 'A' + 'a';
			}
		}

		if (i == 0)
			continue;

		words[nr_words] = (char *)malloc(i + 1);
		if (words[nr_words] == NULL)
			break;

		memcpy(words[nr_words], buf, i + 1);
		nr_words++;
	}

	qsort(words, nr_words, sizeof(char *), &cmp);
}

static int is_word(const char *what)
{
	register int low, high, mid;
	register int t;

	if (what == NULL || what[0] == '\0')
		return 0;

	for (low = 0, high = nr_words - 1; low <= high;) {
		mid = (low + high) >> 1;

		t = strcmp(words[mid], what);

		if (t == 0)
			return 1;
		else if (t < 0)
			low = mid + 1;
		else if (t > 0)
			high = mid - 1;
	}

	return 0;
}

int main()
{
	int i, j, k, n;
	char *p, *q;

	read();

	wordlen = (int *)malloc(nr_words * sizeof(int));
	for (i = 0; i < nr_words; i++)
		wordlen[i] = strlen(words[i]);

	wordmrk = (unsigned char *)malloc(i = ((nr_words + 7) / 8));
	memset(wordmrk, '\0', i);

	for (i = 0; i < nr_words; i++) {
		n = wordlen[i];
		for (j = i + 1; j < nr_words && wordlen[j] > n; j++) {
			p = words[i];
			q = words[j];
			for (k = 0; k < n && *p++ == *q++; k++);

			if (k == n && is_word(q))
				MARKWORD(j);
			else if (k < n)
				break;
		}
	}

	for (i = 0; i < nr_words; i++)
		if (ISMARKED(i))
			printf("%s\n", words[i]);

	fflush(stdout);
	return 0;
}

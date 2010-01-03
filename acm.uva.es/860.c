#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_WORDS	131072
#define MAX_LEN		22
#define HTAB_SIZE	16381

typedef unsigned long u_int32_t;

struct dictent {
	u_int32_t hash;
	int len, next, count;
	char data[MAX_LEN+1];
};

static struct dictent dict[MAX_WORDS+10];
static int dict_htab[HTAB_SIZE], dict_len, total_words;
static int ctab[256];

static void dict_clear()
{
	dict_len = 0;
	memset(dict_htab, 0, sizeof(dict_htab));
}

static void dict_add(const char *s, int len)
{
	static u_int32_t h, hm;
	register int i;

	for (h = 0, i = 0; i < len; i++)
		h = ((h << 5) | (h >> 27)) + s[i];
	hm = h % HTAB_SIZE;

	for (i = dict_htab[hm]; i != 0; i = dict[i].next) {
		if (dict[i].hash == h && dict[i].len == len &&
		    memcmp(dict[i].data, s, len) == 0) {
			dict[i].count++;
			return;
		}
	}

	if ((dict_len + 1) >= MAX_WORDS)
		return;

	i = ++dict_len;
	dict[i].hash = h;
	dict[i].len = len;
	dict[i].count = 1;
	dict[i].next = dict_htab[hm];
	dict_htab[hm] = i;
	memcpy(dict[i].data, s, len);
	dict[i].data[len] = '\0';
}

static int readw(char *s)
{
	int n, c;

	for (n = 0; (c = getchar()) != EOF;) {
		if (ctab[(unsigned)c])
			s[n++] = ctab[(unsigned)c];
		else if (n != 0)
			break;
	}

	s[n] = 0;
	return n;
}

static int readt()
{
	static char s[MAX_LEN+1];
	int len;

	dict_clear();
	total_words = 0;

	while ((len = readw(s)) > 0) {
		if (strcmp(s, "****END_OF_TEXT****") == 0)
			return 0;

		if (strcmp(s, "****END_OF_INPUT****") == 0)
			return 1;

		total_words++;
		dict_add(s, len);
	}

	return (dict_len > 0) ? 0 : 1;
}

int main()
{
	static double e, erel, ly;
	int i, c;

	for (i = 0; i < 256; i++) ctab[i] = i;
	for (i = 0; (c = ",.:;!?\"() \t\n"[i]) != '\0'; i++) ctab[c] = 0;
	for (i = 0; i < 26; i++) ctab['a' + i] = 'A' + i;

	while (readt() == 0) {
		ly = log10(total_words);
		for (e = 0., i = 1; i <= dict_len; i++)
			e += (double)dict[i].count * (ly - log10(dict[i].count));
		e /= (double)total_words;

		erel = 100. * e / ly;

		printf("%d %.1f %.0f\n", total_words, e, erel);
	}

	return 0;
}

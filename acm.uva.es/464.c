#include <stdio.h>
#include <string.h>

static int k, w;

static void put(char *s)
{
	printf(w++ ? " %s" : "%s", s);
}

static void empty()
{
	return;
}

static void preposition()
{
	static char *data[] = { "on", "over", "through" };
	put(data[k++ % 3]);
}

static void adverb()
{
	static char *data[] = { "nearly", "suddenly", "restlessly" };
	put(data[k++ % 3]);
}

static void adjective()
{
	static char *data[] = { "green", "small", "rabid", "quick" };
	put(data[k++ % 4]);
}

static void article()
{
	put((k++ & 1) ? "a" : "the");
}

static void intrans_verb()
{
	static char *data[] = { "slept", "jumped", "walked", "swam" };
	put(data[k++ % 4]);
}

static void trans_verb()
{
	static char *data[] = { "struck", "saw", "bit", "took" };
	put(data[k++ % 4]);
}

static void noun()
{
	static char *data[] = { "man", "dog", "fish", "computer", "waves" };
	put(data[k++ % 5]);
}

static void modifier()
{
	if ((k++ & 1) == 0) {
		adjective();
	} else {
		adverb();
		adjective();
	}
}

static void modified_noun()
{
	if ((k++ & 1) == 0) {
		noun();
	} else {
		modifier();
		noun();
	}
}

static void noun_phrase()
{
	article();
	modified_noun();
}

static void verb_phrase()
{
	if ((k++ & 1) != 0)
		adverb();
	trans_verb();
}

static void intrans_verb_phrase()
{
	if ((k++ & 1) != 0)
		adverb();
	intrans_verb();
}

static void prep_phrase()
{
	if ((k++ & 1) == 0) {
		preposition();
		noun_phrase();
	}
}

static void intrans_sentence()
{
	noun_phrase();
	intrans_verb_phrase();
	prep_phrase();
}

static void trans_sentence()
{
	noun_phrase();
	verb_phrase();
	noun_phrase();
	prep_phrase();
}

static void sentence()
{
	if ((k++ & 1) == 0)
		trans_sentence();
	else
		intrans_sentence();
}

int main()
{
	static char s[512];
	static struct {
		char *name;
		void (*f)(void);
	} tab[] = {
		{ "sentence", &sentence },
		{ "trans-sentence", &trans_sentence },
		{ "intrans-sentence", &intrans_sentence },
		{ "subject", &noun_phrase },
		{ "object", &noun_phrase },
		{ "prep-phrase", &prep_phrase },
		{ "intrans-verb-phrase", &intrans_verb_phrase },
		{ "verb-phrase", &verb_phrase },
		{ "noun-phrase", &noun_phrase },
		{ "modified-noun", &modified_noun },
		{ "modifier", &modifier },
		{ "noun", &noun },
		{ "trans-verb", &trans_verb },
		{ "intrans-verb", &intrans_verb },
		{ "article", &article },
		{ "adjective", &adjective },
		{ "adverb", &adverb },
		{ "preposition", &preposition },
		{ "empty", &empty },
		{ NULL, NULL }
	};
	int i;

	for (k = 1; scanf(" %[-A-Za-z]", s) == 1;) {
		for (i = 0; s[i]; i++)
			if (s[i] >= 'A' && s[i] <= 'Z') s[i] |= 0x20;

		for (w = 0, i = 0; tab[i].name; i++)
			if (strcmp(tab[i].name, s) == 0) {
				tab[i].f();
				break;
			}

		printf("\n");
	}

	return 0;
}

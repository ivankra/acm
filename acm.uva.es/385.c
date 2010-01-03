#include <stdio.h>
#include <string.h>

static int comp[256], ind[256];

static char *tab[4][4][4] = {
	{ { "Phe", "Phe", "Leu", "Leu" },
	  { "Ser", "Ser", "Ser", "Ser" },
	  { "Tyr", "Tyr", NULL, NULL },
	  { "Cys", "Cys", NULL, "Trp" } },
	{ { "Leu", "Leu", "Leu", "Leu" },
	  { "Pro", "Pro", "Pro", "Pro" },
	  { "His", "His", "Gln", "Gln" },
	  { "Arg", "Arg", "Arg", "Arg" } },
	{ { "Ile", "Ile", "Ile", "Met" },
	  { "Thr", "Thr", "Thr", "Thr" },
	  { "Asn", "Asn", "Lys", "Lys" },
	  { "Ser", "Ser", "Arg", "Arg" } },
	{ { "Val", "Val", "Val", "Val" },
	  { "Ala", "Ala", "Ala", "Ala" },
	  { "Asp", "Asp", "Glu", "Glu" },
	  { "Gly", "Gly", "Gly", "Gly" } }
};

static int check(char *s)
{
	static char *seq[1024];
	int i, k;

	s = strstr(s, "ATG");
	if (s == NULL)
		return 0;

	s += 3;

	for (k = 0;;) {
		if (s[0] == '\0' || s[1] == '\0' || s[2] == '\0')
			return 0;

		seq[k] = tab[ind[s[0]]][ind[s[1]]][ind[s[2]]];

		if (seq[k] == NULL)
			break;

		k++;
		s += 3;
	}

	if (k == 0)
		return 0;

	for (i = 0; i < k; i++)
		printf((i + 1) >= k ? "%s\n" : "%s-", seq[i]);

	return 1;
}

static void rev(char *s)
{
	register int i, j, k;
	
	for (j = 0; s[j]; j++);

	for (i = 0, j--; i < j;) {
		k = s[i];
		s[i++] = s[j];
		s[j--] = k;
	}
}

int main()
{
	static char s[1024];
	int i;

	for (i = 0; i < 256; i++)
		comp[i] = i;
	comp['A'] = 'T';
	comp['T'] = 'A';
	comp['C'] = 'G';
	comp['G'] = 'C';

	ind['T'] = 0;
	ind['C'] = 1;
	ind['A'] = 2;
	ind['G'] = 3;

	while (scanf(" %[ACGT*]", s) == 1 && strchr(s, '*') == NULL) {
		if (check(s)) continue;

		rev(s);
		if (check(s)) continue;

		for (i = 0; s[i]; i++) s[i] = comp[s[i]];
		if (check(s)) continue;

		rev(s);
		if (check(s)) continue;

		printf("*** No translatable DNA found ***\n");
	}

	return 0;
}

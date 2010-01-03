#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *name[] = { "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#" };

int name2id(char *s)
{
	static struct { char *s; int n; } tab[] = {
		{ "a", 0 },
		{ "a#", 1 }, { "bb", 1 },
		{ "b", 2 }, { "cb", 2 },
		{ "c", 3 }, { "b#", 3 },
		{ "c#", 4 }, { "db", 4 },
		{ "d", 5 },
		{ "d#", 6 }, { "eb", 6 },
		{ "e", 7 }, { "fb", 7 },
		{ "f", 8 }, { "e#", 8 },
		{ "f#", 9 }, { "gb", 9 },
		{ "g", 10 },
		{ "g#", 11 }, { "ab", 11 },
		{ NULL, 0 }
	};
	char t[4];
	int i;

	while (!isalpha(*s));
	for (i = 0; i < 2 && (isalpha(*s) || *s == '#'); i++, s++)
		t[i] = tolower(*s);
	t[i] = '\0';

	for (i = 0; tab[i].s; i++)
		if (strcmp(tab[i].s, t) == 0) return tab[i].n;

	return 12;
}

int main()
{
	static char s[1024];
	int a[4], b[16], i;
	char *p;

	while (gets(s)) {
		memset(b, 0, sizeof(b));
		for (p = s, i = 0; i < 3; i++) {
			while (*p && !isalpha(*p)) p++;
			a[i] = name2id(p);
			b[a[i]]++;
			while (*p && (isalpha(*p) || *p == '#')) p++;
		}

		for (i = 0; i < 12; i++)
			if (b[i] == 1 && b[(i+4)%12] == 1 && b[(i+7)%12] == 1)
				break;

		if (i < 12) {
			printf("%s is a %s Major chord.\n", s, name[i]);
			continue;
		}

		for (i = 0; i < 12; i++)
			if (b[i] == 1 && b[(i+3)%12] == 1 && b[(i+7)%12] == 1)
				break;

		if (i < 12) {
			printf("%s is a %s Minor chord.\n", s, name[i]);
			continue;
		}

		printf("%s is unrecognized.\n", s);
	}

	return 0;
}

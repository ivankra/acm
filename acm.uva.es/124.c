#include <stdio.h>
#include <string.h>

static char ord[256], let[256];
static int rel[32][32], n;

static void try(int k)
{
	int i, a, c;

	if (k == n) {
		ord[n] = '\0';
		printf("%s\n", ord);
		return;
	}

	for (a = 0; a < n; a++) {
		for (c = let[a], i = 0; i < k; i++)
			if (ord[i] == c || rel[c - 'a'][ord[i] - 'a']) break;

		if (i < k)
			continue;

		ord[k] = c;
		try(k + 1);
	}
}

static void sort(char *s, int k)
{
	register int i, j, t;

	for (i = 1; i < k; i++) {
		for (t = s[i], j = i - 1; j >= 0 && s[j] > t; j--)
			s[j + 1] = s[j];
		s[j + 1] = t;
	}
}

int main()
{
	static char buf[4096];
	static int islwr[256], t;
	char *s;
	int i;

	for (i = 0; i < 256; i++)
		islwr[i] = (i >= 'a' && i <= 'z');

	for (t = 0; gets(buf); t++) {
		for (s = buf, i = 0; *s; s++)
			if (islwr[*s]) let[i++] = *s;
		n = i;

		if (i == 0)
			continue;

		sort(let, n);

		memset(rel, 0, sizeof(rel));

		gets(buf);

		for (s = buf;;) {
			while (*s && !islwr[*s]) s++;
			if (*s == '\0') break;

			i = *s++ - 'a';

			while (*s && !islwr[*s]) s++;
			if (*s == '\0') break;

			rel[i][*s++ - 'a'] = 1;
		}

		if (t != 0)
			printf("\n");

		try(0);
	}

	return 0;
}

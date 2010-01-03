#include <stdio.h>
#include <string.h>

char words[1024][32];
int islet[256], isletz[256], nwords;

int parse(int a[], char *s)
{
	int i, n;
	char *q;

	for (n = 0;;) {
		while (!isletz[*s]) s++;

		if (*s == '\0')
			break;

		for (q = words[nwords]; islet[*s];)
			*q++ = *s++;
		*q = '\0';

		for (i = 0; i < nwords; i++)
			if (strcmp(words[i], words[nwords]) == 0) break;

		if (i < nwords)
			a[n++] = i;
		else
			a[n++] = nwords++;
	}

	return n;
}

int main()
{
	static char s1[1024], s2[1024];
	static int a[1024], b[1024], t1[1024], t2[1024], n, m, c;
	int i, j, *t, *q;

	for (i = 0; i < 256; i++) islet[i] = 0;
	for (i = 'a'; i <= 'z'; i++) islet[i] = 1;
	for (i = 'A'; i <= 'Z'; i++) islet[i] = 1;
	for (i = '0'; i <= '9'; i++) islet[i] = 1;
	for (i = 0; i < 256; i++) isletz[i] = islet[i];
	isletz[0] = 1;

	for (c = 1; gets(s1) && gets(s2); c++) {
		if (s1[0] == '\0' || s2[0] == '\0') {
			printf("%2d. Blank!\n", c);
			continue;
		}

		nwords = 0;

		n = parse(a + 1, s1);
		m = parse(b + 1, s2);

		for (t = t1, q = t2, i = 0; i <= m; i++)
			t[i] = 0;

		for (i = 1; i <= n; i++) {
			for (q[0] = 0, j = 1; j <= m; j++) {
				if (a[i] == b[j])
					q[j] = t[j - 1] + 1;
				else if (q[j - 1] >= t[j])
					q[j] = q[j - 1];
				else
					q[j] = t[j];
			}

			t = q;
			q = (q == t1) ? t2 : t1;
		}

		printf("%2d. Length of longest match: %d\n", c, t[m]);
	}

	return 0;
}

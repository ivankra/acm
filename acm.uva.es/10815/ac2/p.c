#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIV	65537
#define MAXW	8192

int read(int, char *, int);
int write(int, char *, int);

char inbuf[1048576], wordbuf[1048576], *words[MAXW];
int isalp[256], isalpz[256], tab_next[MAXW], htab[DIV], nwords;

static void sort(char **a, int n)
{
	int i, j;
	char *p, *t;

re:	if (n < 32) {
		for (i = 1; i < n; i++) {
			for (t = a[i], j = i - 1; j >= 0 && strcmp(a[j], t) > 0; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}
		return;
	}

	p = a[(n - 1) >> 1];

	for (i = -1, j = n;;) {
		while (strcmp(a[++i], p) < 0);
		while (strcmp(a[--j], p) > 0);

		if (i >= j) break;

		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	if ((n - i) > 1)
		sort(a + i, n - i);

	n = i;
	goto re;
}

void main2()
{
	char *inp, *s, *wordp;
	int i, k;

	for (i = 'a'; i <= 'z'; i++) isalp[i] = isalpz[i] = 1;
	for (i = 'A'; i <= 'Z'; i++) isalp[i] = isalpz[i] = 1;
	isalpz[0] = 1;

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = '\0';

	nwords = 0;
	wordp = wordbuf;

	for (;;) {
next_word:
		while (!isalpz[*(unsigned char *)inp]) inp++;

		if (*inp == '\0')
			break;

		s = wordp;
		k = (*s++ = *inp++ | 0x20) - 'a';

		while (isalp[*(unsigned char *)inp]) {
			k = (k << 5) | ((*s++ = *inp++ | 0x20) - 'a');
			if (k >= DIV) k %= DIV;
		}
		*s++ = '\0';

		for (i = htab[k]; i != 0; i = tab_next[i])
			if (strcmp(words[i], wordp) == 0) goto next_word;

		words[++nwords] = wordp;
		wordp = s;
		tab_next[nwords] = htab[k];
		htab[k] = nwords;
	}

	sort(words + 1, nwords);

	for (i = 1, inp = inbuf; i <= nwords; i++) {
		for (s = words[i]; *s;)
			*inp++ = *s++;
		*inp++ = '\n';
	}
	write(1, inbuf, inp - inbuf);

	exit(0);
}

int main()
{
	main2();
	return 0;
}

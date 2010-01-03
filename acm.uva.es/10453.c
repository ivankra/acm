#include <stdio.h>

static char s[1024];
static int n;
static int pallen[1024][1024];   /* pallen[k][i]: length of min. palindrome
				    constructed from substring s[i .. i+k-1] */

static void make_pallen(void)
{
	register int i, k, m;

	for (i = 0; i < 1024; i++)
		pallen[0][i] = 0;

	for (i = 0; i < n; i++)
		pallen[1][i] = 1;

	for (k = 2; k <= n; k++) {
		m = n - k;
		for (i = 0; i <= m; i++) {
			if (s[i] == s[i + k - 1])
				pallen[k][i] = pallen[k-2][i+1] + 2;
			else if (pallen[k-1][i] <= pallen[k-1][i+1])
				pallen[k][i] = pallen[k-1][i] + 2;
			else
				pallen[k][i] = pallen[k-1][i+1] + 2;
		}
	}
}

static void construct(char *r)
{
	register int i, k;
	register char *p, *q;

	p = r;                   /* 'prepend' pointer */
	q = r + pallen[n][0];    /* 'append' pointer */
	*q-- = '\0';

	for (k = n, i = 0; k > 0;) {
		if (s[i] == s[i + k - 1]) {
			*p++ = s[i];
			*q-- = s[i];
			k -= 2;
			i++;
			/* expand central substring */
		} else if (pallen[k-1][i] < pallen[k-1][i+1]) {
			*p++ = s[i + k - 1];
			*q-- = s[i + k - 1];
			k--;
			/* continue expansion of left substring */
		} else {
			*p++ = s[i];
			*q-- = s[i];
			k--;
			i++;
			/* continue expansion of right substring (i=i+1) */
		}
	}
}

int main()
{
	static char line[2048], pal[2048];
	int i;

	while (fgets(line, sizeof(line), stdin)) {
		for (i = 0, n = 0; line[i]; i++)
			if (line[i] >= 'a' && line[i] <= 'z')
				s[n++] = line[i];
		s[n] = '\0';

		make_pallen();

		construct(pal);

		printf("%d %s\n", pallen[n][0] - n, pal);
	}

	return 0;
}

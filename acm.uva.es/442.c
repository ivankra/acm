#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	static int rows[26], cols[26];
	static int stkr[65536], stkc[65536];
	int i, c, n, k, e, m;

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		while ((c = getchar()) != EOF && !isalpha(c));
		if (c == EOF) return 0;
		c = toupper(c) - 'A';
		scanf("%d %d\n", &rows[c], &cols[c]);
	}

	while ((c = getchar()) != EOF && c != '(' && !isalpha(c));
	ungetc(c, stdin);

	for (e = 0, m = 0, k = 0;;) {
		c = getchar();
		if (isalpha(c)) {
			c = toupper(c) - 'A';
			stkr[k] = rows[c];
			stkc[k++] = cols[c];
		} else if (c == ')') {
			if (k < 2) { e++; continue; }
			k -= 2;
			if (e == 0 && stkc[k] == stkr[k+1]) {
				m += stkr[k] * stkc[k] * stkc[k+1];
				stkc[k] = stkc[k + 1];
				k++;
			} else {
				e = 1;
			}
		} else if (c == '\n' || c == EOF) {
			if (e)
				printf("error\n");
			else if (k > 0)
				printf("%d\n", m);
			e = 0;
			m = 0;
			k = 0;
			if (c == EOF) break;
		}
	}

	return 0;
}

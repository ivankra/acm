/* Problem 10405. "Longest Common Subsequence." */
#include <stdio.h>

#define MAXLEN 1001

int tab_1[MAXLEN], tab_2[MAXLEN];
char a[MAXLEN+5], b[MAXLEN+5];

int main()
{
	int i, j, m, n;
	int *tab, *tab_next;

	while (fgets(a, sizeof(a), stdin) && fgets(b, sizeof(b), stdin)) {
		for (m = 0; a[m] && a[m] != '\n'; m++);
		for (n = 0; b[n] && b[n] != '\n'; n++);

		tab = tab_1;
		tab_next = tab_2;

		for (i = 0; i < n; i++)
			tab[i] = 0;

		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++) {
				if (a[i] == b[j]) {
					tab_next[j] = 1 + tab[j - 1];
				} else {
					tab_next[j] = tab[j];
					if (j > 0 && tab_next[j-1] > tab_next[j])
						tab_next[j] = tab_next[j-1];
				}
			}

			if (tab == tab_1) {
				tab = tab_2;
				tab_next = tab_1;
			} else {
				tab = tab_1;
				tab_next = tab_2;
			}
		}

		printf("%d\n", (n > 0) ? tab[n - 1] : 0);
	}

	return 0;
}

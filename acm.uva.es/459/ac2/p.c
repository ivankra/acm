#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <memory.h>

static int adj[32][32], t, n;
static int grp[32], ngrp;

static void fill(int k, int g)
{
	static int stack[128], sp;
	register int i;

	for (stack[0] = k, sp = 1; sp > 0;) {
		k = stack[--sp];
		for (grp[k] = g, i = 0; i < 32; i++) {
			if (adj[k][i] && grp[i] == 0) {
				grp[i] = k;
				stack[sp++] = i;
			}
		}
	}
}

int main()
{
	register int i, c;

	scanf("%d", &t);

	while (t-- > 0) {
		while ((c = getchar()) != EOF && !isalpha(c));

		if (c == EOF)
			break;

		n = toupper(c) - 'A' + 1;

		memset(adj, 0, sizeof(adj));

		for (i = 0;;) {
			while ((c = getchar()) != EOF && c != '\n' && !isalpha(c));
			if (c == EOF) {
				break;
			} else if (c == '\n') {
				if (i != 0) break;
				i = 1;
			} else {
				while ((i = getchar()) != EOF && !isalpha(i));
				if (i == EOF) break;
				c = toupper(c) - 'A';
				i = toupper(i) - 'A';
				adj[c][i] = 1;
				adj[i][c] = 1;
				i = 0;
			}
		}

		memset(grp, 0, sizeof(grp));
		ngrp = 0;

		for (i = 0; i < n; i++)
			if (grp[i] == 0) fill(i, ++ngrp);

		printf("%d\n", ngrp);

		if (t > 0)
			printf("\n");
	}

	return 0;
}

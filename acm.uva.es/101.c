/* Problem 101 "The Blocks Problem" */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXN	30		/* max number of blocks */

char *getword()
{
	static char buf[128];
	int i, c;

	while ((c = getchar()) != EOF && (strchr(" \t\r\n", c) != NULL));
	if (c == EOF) return NULL;

	for (i = 0; i < (sizeof(buf) - 1);) {
		buf[i++] = tolower(c);
		c = getchar();
		if (c == EOF || strchr(" \t\r\n", c) != NULL) break;
	}

	buf[i] = '\0';

	return buf;
}

struct place {
	int count;		/* number of blocks at this place on the table */
	int b[MAXN];		/* blocks: b[0] is bottom, b[count] is top */
};

struct place tab[MAXN];

int where(int blk)
{
	int i, j;

	for (i = 0; i < MAXN; i++)
		for (j = 0; j < tab[i].count; j++)
			if (tab[i].b[j] == blk)
				return i;

	fprintf(stderr, "where(): block %d does not exist\n", blk);
	exit(-1);
}

void free_top_of(int blk)
{
	int i, j, x, p = where(blk);

	for (i = 0; tab[p].b[i] != blk; i++);

	for (x = ++i; i < tab[p].count; i++) {
		j = tab[p].b[i];
		tab[j].b[tab[j].count++] = j;	/* return to position 'j' */
	}

	tab[p].count = x;
}

void pile_over(int a, int b)
{
	int ap = where(a), bp = where(b), i, x;

	for (i = 0; tab[ap].b[i] != a; i++);
	x = i;

	for (; i < tab[ap].count; i++)
		tab[bp].b[tab[bp].count++] = tab[ap].b[i];

	tab[ap].count = x;
}

int main()
{
	int i, a, b, blk_count;
	char *w, what, how;

	blk_count = atoi(getword());

	for (i = 0; i < MAXN; i++) {
		tab[i].count = (i < blk_count) ? 1 : 0;
		tab[i].b[0] = i;
	}

	while ((w = getword()) != NULL) {
		if (strcmp(w, "move") == 0)
			what = 'm';
		else if (strcmp(w, "pile") == 0)
			what = 'p';
		else
			break;

		a = atoi(getword());
		how = (strcmp(getword(), "onto") == 0) ? 'n' : 'v';
		b = atoi(getword());

		if (a < 0 || a >= blk_count || b < 0 || b >= blk_count)
			continue;
		if (where(a) == where(b))
			continue;

		if (what == 'm')	/* move */
			free_top_of(a);

		if (how == 'n')		/* onto */
			free_top_of(b);

		pile_over(a, b);
	}

	for (i = 0; i < blk_count; i++) {
		printf("%d:", i);
		for (a = 0; a < tab[i].count; a++)
			printf(" %d", tab[i].b[a]);
		printf("\n");
	}

	return 0;
}

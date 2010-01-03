#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned loc_t[3];

#define SET(L,k) ((L)[(k) >> 5] |= 1U << ((k) & 31))
#define CLR(L,k) ((L)[(k) >> 5] &= ~(1U << ((k) & 31)))
#define GET(L,k) (((unsigned)((L)[(k) >> 5]) >> ((k) & 31U)) & 1U)

/* a group == a row, a column or a square
   each group contains 9 cells */
typedef struct {
	int cells[9], contains[81];
	int id, type;
	loc_t loc;
} group_t;

group_t *grps, *rows, *cols, *sqrs;

struct {
	int row, col, sqr, adj[32];
	loc_t adjloc;
} cells[81];

int cell_at[16][16], nbits[2048], sbit[2048], nsol, sol1[81];

/* solver's state */
typedef struct {
	int a[81];		/* grid; 0's indicate not-yet-filled positions */
	int cand[81];		/* list of candidates for each cell */
	loc_t loc[10];		/* bitmap holding possible locations for each digit */
} sudoku_t;

int elim(sudoku_t *s, int x, int d)
{
	if (s->cand[x] & (1 << d)) {
		s->cand[x] &= ~(1 << d);
		CLR(s->loc[d], x);
		return 1;
	} else {
		return 0;
	}
}

int place(sudoku_t *s, int x, int d)
{
	int i;

	s->a[x] = d;
	s->cand[x] = 0;

	for (i = 0; i < 20; i++)
		if ((s->cand[cells[x].adj[i]] &= ~(1 << d)) == 0 &&
		    s->a[cells[x].adj[i]] == 0)
			return 1;

	for (i = 0; i < 3; i++)
		s->loc[d][i] &= ~cells[x].adjloc[i];

	for (i = 1; i <= 9; i++)
		CLR(s->loc[i], x);

	return 0;
}

int logic1(sudoku_t *s)
{
	int d, g1, g2, i, j, r;

	for (g1 = r = 0; g1 < 27; g1++) for (g2 = 0; g2 < 27; g2++) {
		if (grps[g1].type == 's' && grps[g2].type == 's') continue;
		if (grps[g1].type != 's' && grps[g2].type != 's') continue;

		for (d = 1; d <= 9; d++) {
			for (i = 0; i < 3; i++)
				if ((grps[g2].loc[i] | (s->loc[d][i] & grps[g1].loc[i])) != grps[g2].loc[i])
					break;
			if (i < 3) continue;

			for (i = 0; i < 3; i++)
				if ((grps[g2].loc[i] & s->loc[d][i] & grps[g1].loc[i])!=0)
					break;
			if (i == 3) continue;

			for (i = 0; i < 9; i++) {
				j = grps[g2].cells[i];
				if (!grps[g1].contains[j])
					r += elim(s, j, d);
			}
		}
	}

	return r;
}

int logic(sudoku_t *s)
{
	int i, j, k, t;

next:	/* process cells with just 0 or 1 possible numbers */
	for (i = j = k = 0; i < 81; i++) {
		if (s->cand[i] == 0) {
			if (s->a[i] == 0) return 0;
			k++;
			continue;
		}
		if ((s->cand[i] & (s->cand[i] - 1)) != 0) continue;
		if (place(s, i, sbit[s->cand[i]])) return 0;
		j = 1;
	}
	if (k == 81) return 1;
	if (j) goto next;

	/* if a digit may be placed in only in one place in a group, place it there */
	for (i = 0; i < 27; i++) {
		for (j = 1; j <= 9; j++) {
#if 0
			for (k = 0; k < 9 && GET(s->loc[j], grps[i].cells[k]) == 0; k++);
			if (k == 9) continue;
			for (t = k+1; t < 9 && GET(s->loc[j], grps[i].cells[t]) == 0; t++);
			if (t < 9) continue;
#else
			for (k = 0; k < 9 && ((s->cand[grps[i].cells[k]] >> j) & 1) == 0; k++);
			if (k == 9) continue;
			for (t = k+1; t < 9 && ((s->cand[grps[i].cells[t]] >> j) & 1) == 0; t++);
			if (t < 9) continue;
#endif
			if (place(s, grps[i].cells[k], j)) return 0;
			goto next;
		}
	}

	if (logic1(s)) goto next;

	return -1;
}

void prep()
{
	int i, j, k;

	grps = (group_t *)malloc(27 * sizeof(group_t));
	memset(grps, 0, 27 * sizeof(group_t));
	rows = grps;
	cols = &grps[9];
	sqrs = &grps[18];

	for (i = k = 0; i < 9; i++) {
		for (j = 0; j < 9; j++, k++) {
			cell_at[i][j] = k;
			cells[k].row = i;
			rows[i].cells[rows[i].id++] = k;
			cells[k].col = j;
			cols[j].cells[cols[j].id++] = k;
			cells[k].sqr = (i / 3) * 3 + (j / 3);
			sqrs[cells[k].sqr].cells[sqrs[cells[k].sqr].id++] = k;
		}
	}

	for (i = 0; i < 27; i++) grps[i].id = i;
	for (i = 0; i < 9; i++) rows[i].type = 'r';
	for (i = 0; i < 9; i++) cols[i].type = 'c';
	for (i = 0; i < 9; i++) sqrs[i].type = 's';

	for (i = 0; i < 27; i++)
		for (j = 0; j < 9; j++)
			grps[i].contains[grps[i].cells[j]] = 1;

	for (i = 0; i < 81; i++) {
		for (k = 0, j = 0; j < 81; j++)
			if ((cells[i].row == cells[j].row ||
			     cells[i].col == cells[j].col ||
			     cells[i].sqr == cells[j].sqr) && i != j)
				cells[i].adj[k++] = j;
		cells[i].adj[k++] = i;
	}

	for (i = 0; i < 27; i++)
		for (j = 0; j < 9; j++)
			SET(grps[i].loc, grps[i].cells[j]);

	for (i = 0; i < 81; i++)
		for (j = 0; j < 21; j++)
			SET(cells[i].adjloc, cells[i].adj[j]);

	for (i = 0; i < 1024; i++) {
		for (j = i, k = 0; j > 0; k++, j &= j - 1);
		nbits[i] = k;
	}

	for (i = 0; i < 11; i++)
		sbit[1 << i] = i;
}

void backtrack(sudoku_t *s)
{
	sudoku_t t;
	int i, k;

	if (nsol >= 2) return;

	if ((i = logic(s)) >= 0) {
		if (i != 1) return;
		if (nsol == 1 && memcmp(s->a, sol1, 81*sizeof(int)) == 0) return;
		nsol++;
		memcpy(sol1, s->a, 81*sizeof(int));
		return;
	}

	for (i = 0, k = -1; i < 81; i++)
		if (s->a[i] == 0 && (k < 0 || nbits[s->cand[i]] < nbits[s->cand[k]])) k = i;

	for (i = 1; i <= 9; i++) {
		if (((s->cand[k] >> i) & 1) == 0) continue;

		memcpy(&t, s, sizeof(sudoku_t));
		if (place(&t, k, i)) continue;

		backtrack(&t);
	}
}

void initfrom(sudoku_t *s, int a[])
{
	int i, c;

	for (i = 0; i < 81; i++) {
		s->a[i] = 0;
		s->cand[i] = (1 << 10) - 2;
	}

	for (c = 0; c < 10; c++) {
		s->loc[c][0] = s->loc[c][1] = s->loc[c][2] = 0;
		for (i = 0; i < 81; i++) SET(s->loc[c], i);
	}

	for (i = 0; i < 81; i++)
		if (a[i] != 0) place(s, i, a[i]);
}

int sread(sudoku_t *s)
{
	int a[81], i, c;

	for (i = 0; i < 81 && (c = getchar()) != EOF;)
		if ('1' <= c && c <= '9')
			a[i++] = c - '0';
		else if (strchr("0.o?", c) != NULL)
			a[i++] = 0;

	if (i < 81) return 0;

	initfrom(s, a);
	return 1;
}

void solve(sudoku_t *s)
{
	sudoku_t t;
	int a[81], i, j;

	initfrom(&t, s->a);
	nsol = 0;
	backtrack(&t);
	assert(nsol > 0);

	memcpy(a, (nsol == 1) ? s->a : sol1, 81*sizeof(int));

	for (i = 0; i < 81; i++) {
		if (s->a[i] != 0 || a[i] == 0) continue;

		j = a[i];
		a[i] = 0;

		initfrom(&t, a);
		nsol = 0;
		backtrack(&t);
		assert(nsol > 0);

		if (nsol > 1)
			a[i] = j;
	}

	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++)
			putchar(".123456789"[a[cell_at[i][j]]]);
		printf("\n");
	}
}

int main()
{
	int t;
	sudoku_t s;

	prep();
	for (scanf("%d", &t); t-- > 0 && sread(&s);) {
		solve(&s);
		if (t > 0) printf("\n");
	}

	return 0;
}

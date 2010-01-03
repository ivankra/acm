#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* bidirectional bfs */

char final[21] = {0,3,4,3,0,5,6,5,0,1,2,1,0,7,8,7,0,9,10,9,0};

struct path_struct {
	char loc[21], dist;
	char path[10];
} backq[16384];

struct path_struct *back[16384];

int nback;

static void rot1(char y[], char x[])
{
	register int i;

	y[0] = x[10];
	y[1] = x[11];

	for (i = 0; i <= 9; i++)
		y[i + 2] = x[i];

	for (i = 12; i < 21; i++)
		y[i] = x[i];
}

static void rot2(char y[], char x[])
{
	register int i;

	for (i = 0; i <= 8; i++)
		y[i] = x[i];

	for (i = 9; i <= 18; i++)
		y[i] = x[i + 2];

	y[19] = x[9];
	y[20] = x[10];
}

static void rot3(char y[], char x[])
{
	register int i;

	for (i = 0; i <= 9; i++)
		y[i] = x[i + 2];

	y[10] = x[0];
	y[11] = x[1];

	for (i = 12; i < 21; i++)
		y[i] = x[i];
}

static void rot4(char y[], char x[])
{
	register int i;

	for (i = 0; i <= 8; i++)
		y[i] = x[i];

	for (i = 9; i <= 18; i++)
		y[i + 2] = x[i];

	y[9] = x[19];
	y[10] = x[20];
}

static int compare(const void *p, const void *q)
{
	struct path_struct *x, *y;
	int i;

	x = *(struct path_struct **)p;
	y = *(struct path_struct **)q;

	if ((i = memcmp(x->loc, y->loc, 21)) != 0)
		return i;

	if (x->dist != y->dist)
		return (x->dist > y->dist) ? 1 : -1;

	return strcmp(x->path, y->path);
}

static struct path_struct *find_back(char loc[])
{
	int a, b, c, r;

	for (a = 0, b = nback - 1; a <= b;) {
		c = (a + b) >> 1;
		r = memcmp(back[c]->loc, loc, 21);

		if (r == 0)
			return back[c];	
		else if (r < 0)
			a = c + 1;
		else
			b = c - 1;
	}

	return NULL;
}

static void make_back()
{
	static int rev[5] = { 0, 3, 4, 1, 2 };
	int i, j, p;

	memcpy(backq[0].loc, final, 21);
	backq[0].dist = 0;
	backq[0].path[0] = '\0';
	nback = 1;

	for (p = 0; p < nback && backq[p].dist <= 7; p++) {
		for (i = 1; i <= 4; i++) {
			if (backq[p].path[0] == (i + '0'))
				continue;

			if (i == 1)
				rot1(backq[nback].loc, backq[p].loc);
			else if (i == 2)
				rot2(backq[nback].loc, backq[p].loc);
			else if (i == 3)
				rot3(backq[nback].loc, backq[p].loc);
			else
				rot4(backq[nback].loc, backq[p].loc);

			backq[nback].path[0] = rev[i] + '0';
			strcpy(backq[nback].path + 1, backq[p].path);
			backq[nback].dist = backq[p].dist + 1;
			nback++;
		}
	}

	for (i = 0; i < nback; i++)
		back[i] = &backq[i];
	qsort(back, nback, sizeof(void *), &compare);

	for (i = 1, j = 1; i < nback; i++) {
		if (memcmp(back[i - 1]->loc, back[i]->loc, 21) != 0)
			back[j++] = back[i];
	}

	nback = j;
}

static void solve(char pos[])
{
	static int rev[5] = { 0, 3, 4, 1, 2 };
	static struct path_struct queue[65536];
	struct path_struct *b, *q, *qt;
	int i;

	q = &queue[0];
	memcpy(q->loc, pos, 21);
	q->dist = 0;
	q->path[0] = '\0';
	qt = &queue[1];

	for (; q < qt; q++) {
		if (q->dist > 8)
			break;

		if ((b = find_back(q->loc)) != NULL) {
			printf("%s%s\n", q->path, b->path);
			return;
		}

		for (i = 1; i <= 4; i++) {
			if (q->dist > 0 && q->path[q->dist-1] == (rev[i]+'0'))
				continue;

			if (i == 1)
				rot1(qt->loc, q->loc);
			else if (i == 2)
				rot2(qt->loc, q->loc);
			else if (i == 3)
				rot3(qt->loc, q->loc);
			else
				rot4(qt->loc, q->loc);

			strcpy(qt->path, q->path);
			qt->path[q->dist] = i + '0';
			qt->path[q->dist + 1] = '\0';
			qt->dist = q->dist + 1;

			qt++;
		}
	}

	printf("NO SOLUTION WAS FOUND IN 16 STEPS\n");
}

int main()
{
	char a[32];
	struct path_struct *b;
	int i, p, t;

	make_back();

	for (scanf("%d", &t); t-- > 0;) {
		for (i = 0; i < 24; i++) {
			scanf("%d", &p);
			a[i] = p;
		}

		if (memcmp(a, final, 21) == 0) {
			printf("PUZZLE ALREADY SOLVED\n");
			continue;
		}

		if ((b = find_back(a)) != NULL) {
			printf("%s\n", b->path);
			continue;
		}

		solve(a);
	}

	return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
	int c, x, y;
} term_t;

typedef struct {
	term_t t[256];
	int n;
} poly_t;

int get(poly_t *p, int x, int y)
{
	int i;

	for (i = 0; i < p->n; i++)
		if (p->t[i].x == x && p->t[i].y == y) return p->t[i].c;

	return 0;
}

void set(poly_t *p, int x, int y, int c)
{
	int i;

	for (i = 0; i < p->n; i++) {
		if (p->t[i].x == x && p->t[i].y == y) {
			p->t[i].c = c;
			return;
		}
	}

	p->t[p->n].x = x;
	p->t[p->n].y = y;
	p->t[p->n].c = c;
	p->n++;
}

void take(poly_t *p, char *s)
{
	int i, j, c, x, y;

	p->n = 0;

	for (i = 0; s[i]; i++)
		s[i] = tolower(s[i]);

	for (;;) {
		c = x = y = 0;

		while (*s && !isdigit(*s) && *s != '-' && *s != 'x' && *s != 'y')
			s++;

		if (*s == '\0')
			break;

		for (j = 1; *s == '+' || *s == '-'; s++)
			if (*s == '-') j *= -1;

		while (*s && !isdigit(*s) && *s != 'x' && *s != 'y')
			s++;

		if (isdigit(*s)) {
			for (c = 0; *s && isdigit(*s); s++)
				c = c * 10 + *s - '0';
		} else {
			c = 1;
		}

		c *= j;

		for (;;) {
			while (*s && *s != 'x' && *s != 'y' && *s != '-' && *s != '+')
				s++;

			if (*s != 'x' && *s != 'y')
				break;

			j = *s++;

			if (isdigit(*s)) {
				for (i = 0; *s && isdigit(*s); s++)
					i = i * 10 + *s - '0';
			} else {
				i = 1;
			}

			if (j == 'x')
				x += i;
			else
				y += i;
		}

		set(p, x, y, get(p, x, y) + c);
	}
}

void mul(poly_t *r, poly_t *p, poly_t *q)
{
	int i, j, x, y;

	for (r->n = i = 0; i < p->n; i++) {
		for (j = 0; j < q->n; j++) {
			x = p->t[i].x + q->t[j].x;
			y = p->t[i].y + q->t[j].y;
			set(r, x, y, get(r, x, y) + p->t[i].c * q->t[j].c);
		}
	}
}

int cmp(const void *p, const void *q)
{
	term_t *a = (term_t *)p, *b = (term_t *)q;
	return (a->x != b->x) ? (b->x - a->x) : (a->y - b->y);
}

void print(poly_t *p)
{
	static char s[2][1024];
	int i, z, r, x, y, c;

	set(p, 0, 0, get(p, 0, 0));
	qsort(p->t, p->n, sizeof(p->t[0]), &cmp);

	memset(s, ' ', sizeof(s));

	for (z = 0, r = 0; z < p->n; z++) {
		x = p->t[z].x;
		y = p->t[z].y;
		c = p->t[z].c;

		if (c == 0)
			continue;

		if (r == 0) {
			if (c < 0) {
				s[1][r++] = '-';
				c = -c;
			}
		} else {
			s[1][r++] = ' ';
			if (c < 0) {
				s[1][r++] = '-';
				c = -c;
			} else {
				s[1][r++] = '+';
			}
			s[1][r++] = ' ';
		}

		if (x == 0 && y == 0) {
			r += sprintf(s[1] + r, "%d", c);
			continue;
		}

		if (c != 1)
			r += sprintf(s[1] + r, "%d", c);

		if (x != 0) {
			s[1][r++] = 'x';
			if (x != 1) r += sprintf(s[0] + r, "%d", x);
		}

		if (y != 0) {
			s[1][r++] = 'y';
			if (y != 1) r += sprintf(s[0] + r, "%d", y);
		}
	}

	for (i = 0; i < r; i++) {
		if (s[0][i] == '\0') s[0][i] = ' ';
		if (s[1][i] == '\0') s[1][i] = ' ';
	}
	s[0][r] = s[1][r] = '\0';

	printf("%s\n%s\n", s[0], s[1]);
}

int main()
{
	static char s[65536], t[65536];
	static poly_t p, q, r;

	while (gets(s) && gets(t) && s[0] != '#' && t[0] != '#') {
		take(&p, s);
		take(&q, t);

		mul(&r, &p, &q);
		print(&r);
	}

	return 0;
}

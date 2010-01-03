#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

typedef struct {
	int h, w, c;
	char s[1];
} box_t;

int tok;
char toks[65536];

box_t *make(int h, int w, int c)
{
	box_t *p = (box_t *)malloc(sizeof(box_t) + h * w + 1);
	p->h = h;
	p->w = w;
	p->c = c;
	memset(p->s, ' ', h * w);
	return p;
}

void put(box_t *p, int y, int x, int c)
{
	p->s[y * p->w + x] = c;
}

void copy(box_t *z, int y0, int x0, box_t *p)
{
	int i, j;
	for (i = 0; i < p->h; i++)
		for (j = 0; j < p->w; j++)
			z->s[(y0 + i) * z->w + (x0 + j)] = p->s[i * p->w + j];
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

box_t *join(box_t *a, char op, box_t *b)
{
	box_t *p = make(max(a->c, b->c) + max(a->h - a->c, b->h - b->c),
			a->w + 3 + b->w, max(a->c, b->c));
	copy(p, p->c - a->c, 0, a);
	copy(p, p->c - b->c, a->w + 3, b);
	put(p, p->c, a->w + 1, op);
	free(a);
	free(b);
	return p;
}

int next()
{
	int i, c;

	while ((c = getchar()) != EOF && isspace(c)) c++;
	if (c == EOF) return (tok = EOF);
	if (strchr("+-*/^=(){}", c) != NULL) return (tok = c);

	toks[0] = c;
	for (i = 1; (c = getchar()) != EOF && (isalnum(c) || c == '.');)
		toks[i++] = c;
	toks[i] = '\0';
	if (c != EOF) ungetc(c, stdin);
	return (tok = 's');
}

box_t *level5();

box_t *level1()
{
	box_t *p, *q;
	int i;

	if (tok == '-') {
		next();
		q = level1();
		p = make(q->h, q->w + 1, q->c);
		copy(p, 0, 1, q);
		put(p, q->c, 0, '-');
		free(q);
		return p;
	} else if (tok == '{') {
		next();
		p = level5();
		assert(tok == '}');
		next();
		return p;
	} else if (tok == '(') {
		next();
		q = level5();
		assert(tok == ')');
		next();
		p = make(q->h, q->w + 2, q->c);
		copy(p, 0, 1, q);
		for (i = 0; i < p->h; i++) {
			put(p, i, 0, '(');
			put(p, i, p->w - 1, ')');
		}
		free(q);
		p->c = p->h / 2;
		return p;
	} else {
		assert(tok == 's');
		p = make(1, strlen(toks), 0);
		strcpy(p->s, toks);
		next();
		return p;
	}
}

box_t *level2()
{
	box_t *p, *q, *r;

	p = level1();
	if (tok != '^') return p;

	next();
	q = level2();

	r = make(p->h + q->h, p->w + q->w, p->c + q->h);
	copy(r, q->h, 0, p);
	copy(r, 0, p->w, q);
	free(p);
	free(q);

	return r;
}

box_t *level3()
{
	box_t *p, *q, *r;
	int i;

	for (p = level2();;) {
		if (tok == '*') {
			next(), p = join(p, '*', level2());
		} else if (tok == '/') {
			next();
			r = level2();
			q = make(p->h + 1 + r->h, max(p->w, r->w), p->h);
			if (p->w < r->w) {
				copy(q, 0, (r->w - p->w + 1) / 2, p);
				copy(q, p->h + 1, 0, r);
			} else {
				copy(q, 0, 0, p);
				copy(q, p->h + 1, (p->w - r->w + 1) / 2, r);
			}
			for (i = 0; i < q->w; i++) put(q, p->h, i, '-');
			free(p);
			free(r);
			p = q;
		} else {
			return p;
		}
	}
}

box_t *level4()
{
	box_t *p;
	int op;
	for (p = level3(); tok == '+' || tok == '-';)
		op = tok, next(), p = join(p, op, level3());
	return p;
}

box_t *level5()
{
	box_t *p;
	for (p = level4(); tok == '=';)
		next(), p = join(p, '=', level4());
	return p;
}

int main()
{
	int i, j, t;
	box_t *p;

	next();
	for (t = 0; tok != EOF;) {
		if (t++) printf("\n");

		p = level5();
		for (i = 0; i < p->h; i++) {
			for (j = p->w - 1; j >= 0 && p->s[i * p->w + j] == ' '; j--)
				p->s[i * p->w + j] = 0;
			printf("%.*s\n", p->w, p->s + i * p->w);
		}
		free(p);
	}

	return 0;
}

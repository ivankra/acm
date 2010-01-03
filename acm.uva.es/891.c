#include <stdio.h>

typedef struct {
	int w, h, m;
} box_t;

char *p;

int max(int a, int b)
{
	return (a > b) ? a : b;
}

void expr(box_t *r)
{
	box_t a, b;

	while (*p == ' ' || *p == '\t') p++;

	switch (*p++) {
		case '\"':
			for (r->w = 8; *p++ != '\"'; r->w++);
			r->h = 3;
			r->m = 1;
			break;
		case '(':
			expr(&a);
			expr(&b);
			while (*p++ != ')');
			r->w = a.w + b.w;
			r->m = max(a.m, b.m);
			r->h = r->m + max(a.h - a.m, b.h - b.m);
			break;
		case '{':
			expr(&a);
			expr(&b);
			while (*p++ != '}');
			r->w = max(a.w, b.w) + 4;
			r->h = a.h + b.h + 1;
			r->m = a.m;
			break;
		case '[':
			expr(r);
			while (*p++ != ']');
			r->w += 4;
			r->h++;
			r->m++;
			break;
	}
}

int main()
{
	static char s[65536];
	box_t r;
	int t;

	while (gets(s) && sscanf(s, "%d", &t) != 1);

	while (t-- > 0 && gets(s)) {
		p = s;
		expr(&r);
		printf("%dx%d\n", r.w + 4, r.h);
	}

	return 0;
}

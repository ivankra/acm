#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	int car, cdr;
	char *lit;
} obj_t;

#define CAR(x) (tab[x].car)
#define CDR(x) (tab[x].cdr)
#define LIT(x) (tab[x].lit)

static obj_t *tab;
static int tab_size, tab_used, freelist;

static void clean()
{
	int i;

	CAR(0) = CDR(0) = 0; LIT(0) = NULL;
	for (freelist = 0, tab_used = 1, i = tab_size - 1; i > 0; i--) {
		if (LIT(i)) {
			free(LIT(i));
			LIT(i) = NULL;
		}
		CDR(i) = freelist;
		freelist = i;
	}
}

static void init()
{
	tab_size = 2048;
	tab = (obj_t *)malloc(tab_size * sizeof(obj_t));
	memset(tab, '\0', tab_size * sizeof(obj_t));
	clean();
}

static int cell(int a, int b, char *s)
{
	register int i;

	if (freelist == 0) {
		int m = tab_size;

		tab_size *= 2;
		tab = (obj_t *)realloc(tab, tab_size * sizeof(obj_t));

		for (i = tab_size - 1; i >= m; i--) {
			LIT(i) = NULL;
			CDR(i) = freelist;
			freelist = i;
		}
	}

	i = freelist;
	freelist = CDR(freelist);

	CAR(i) = a;
	CDR(i) = b;

	if (s == NULL) {
		LIT(i) = NULL;
	} else {
		LIT(i) = (char *)malloc(strlen(s) + 1);
		strcpy(LIT(i), s);
	}

	tab_used++;

	return i;
}

static int sread()
{
	static char buf[4096];
	int k, c;

	for (;;) {
		c = getchar();

		if (c == EOF) return 0;
		if (isspace(c)) continue;

		if (c == ')')
			return -1;

		if (c == '#') {
			buf[0] = '#';
			for (k = 1; (c = getchar()) != EOF && !isspace(c);)
				buf[k++] = c;
			if (c != EOF) ungetc(c, stdin);
			buf[k] = '\0';
			return cell(0, 0, buf);
		}

		if (c == '(') {
			int head, tail;

			if ((k = sread()) == -1)
				return cell(0,0,NULL);  /* ( ) */

			head = tail = cell(k, 0, NULL);

			while ((k = sread()) != -1) {
				k = cell(k, 0, NULL);
				/* tab pointer may be changed now */
				CDR(tail) = k;
				tail = k;
			}

			return head;
		}

		if (c == '\"') {
			buf[0] = '\"';
			for (k = 1; (c = getchar()) != EOF;) {
				buf[k++] = c;
				if (c == '\\')
					buf[k++] = getchar();
				else if (c == '\"')
					break;
			}
			buf[k] = '\0';
			return cell(0, 0, buf);
		}

		buf[0] = c;

		for (k = 1; (c = getchar()) != EOF;) {
			if (isspace(c) || c == '\"' || c == '(' || c == ')' ||
			    c == '\\' || c == '#')
				break;
			buf[k++] = c;
		}

		if (c != EOF)
			ungetc(c, stdin);

		buf[k] = '\0';
		return cell(0, 0, buf);
	}
}

static int col;

#define INDENT(n) { int t; t = (n); col += t;; while (t-- > 0) putchar(' '); }
#define NLINDENT(n) { putchar('\n'); col = 0; INDENT(n); }
#define WRITE(s) { char *p = (s); while (*p) { putchar(*p++); col++; } }
#define WRITEC(c) { putchar(c); col++; }

static void pretty(int x, int ind)
{
	char *s;
	int k, t;

	if (x == -1) {
		WRITEC(')');
		return;
	}

	if (LIT(x) != NULL) {
		/* not a cons */
		WRITE(LIT(x));
		return;
	}

	if (x == 0 || (CAR(x) == 0 && CDR(x) == 0)) {
		WRITE("()");
		return;
	}

	if (LIT(CAR(x)) == NULL) {
		/* ( (head) ... ) */

		WRITEC('(');
		pretty(CAR(x), ind + 1);

		x = CDR(x);

		if (x == 0) {
			WRITEC(')');
			return;
		}

		WRITEC(' ');
		k = col;

		while (x != 0) {
			pretty(CAR(x), k);
			if ((x = CDR(x)) != 0) {
				NLINDENT(k);
			}
		}

		WRITEC(')');
		return;
	}

	if (CDR(x) == 0) {
		/* (id) */
		WRITEC('(');
		WRITE(LIT(CAR(x)));
		WRITEC(')');
		return;
	}

	s = LIT(CAR(x));

	/* choose indentation offset */
	if (strcmp(s, "define") == 0) {
		if (LIT(CAR(CDR(CDR(x)))) != NULL)
			t = 0;
		else
			t = 3;
	} else if (strcmp(s, "lambda") == 0) {
		t = 3;
	} else if (strcmp(s, "if") == 0) {
		t = 4;
	} else {
		for (t = 0, k = x; k != 0; k = CDR(k)) {
			if (LIT(CAR(k)) == NULL) {
				t = strlen(s) + 2;
				break;
			}
		}
	}

	/* t == 0: put everything on the same line */
	if (t == 0) {
		WRITEC('(');
		while (x != 0) {
			WRITE(LIT(CAR(x)));
			if ((x = CDR(x)) != 0) {
				WRITEC(' ');
			}
		}
		WRITEC(')');
		return;
	}

	WRITEC('(');
	WRITE(s);
	WRITEC(' ');

	x = CDR(x);

	k = col;
	ind += t;

	for (k = 0; x != 0; k++) {
		if (k == 0)
			pretty(CAR(x), col);
		else
			pretty(CAR(x), ind);

		if ((x = CDR(x)) != 0) {
			NLINDENT(ind);
		}
	}

	WRITEC(')');
}

int main()
{
	int x;

	init();

	while ((x = sread()) != 0) {
		col = 0;
		pretty(x, 0);
		putchar('\n');

		if (tab_used > 256)
			clean();
	}

	return 0;
}

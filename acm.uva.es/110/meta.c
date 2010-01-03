#include <stdio.h>
#include <string.h>

int write(int, char *, int);

#define NSIMPLE 4

static struct {
	int n;
	char *s;
} simple[NSIMPLE+1] = {
	{ 0, NULL },

	{ 78,  "program sort(input,output);\nvar\na : integer;\nbegin\nreadln(a);\n"
	"writeln(a)\nend.\n" },

	{ 116,	"program sort(input,output);\nvar\na,b : integer;\nbegin\n"
	"readln(a,b);\nif a < b then\nwriteln(a,b)\nelse\nwriteln(b,a)\n"
	"end.\n" },

	{ 260,	"program sort(input,output);\nvar\na,b,c : integer;\nbegin\n"
	"readln(a,b,c);\nif a < b then\nif b < c then\nwriteln(a,b,c)\n"
	"else if a < c then\nwriteln(a,c,b)\nelse\nwriteln(c,a,b)\nelse\n"
	"if a < c then\nwriteln(b,a,c)\nelse if b < c then\nwriteln(b,c,a)\n"
	"else\nwriteln(c,b,a)\nend.\n" },

	{ 924,	"program sort(input,output);\nvar\na,b,c,d : integer;\nbegin\n"
	"readln(a,b,c,d);\nif a < b then\nif b < c then\n"
	"if c < d then\nwriteln(a,b,c,d)\nelse if b < d then\n"
	"writeln(a,b,d,c)\nelse if a < d then\nwriteln(a,d,b,c)\n"
	"else\nwriteln(d,a,b,c)\nelse if a < c then\nif b < d then\n"
	"writeln(a,c,b,d)\nelse if c < d then\nwriteln(a,c,d,b)\n"
	"else if a < d then\nwriteln(a,d,c,b)\nelse\nwriteln(d,a,c,b)\nelse\n"
	"if b < d then\nwriteln(c,a,b,d)\nelse if a < d then\n"
	"writeln(c,a,d,b)\nelse if c < d then\nwriteln(c,d,a,b)\nelse\n"
	"writeln(d,c,a,b)\nelse\nif a < c then\nif c < d then\n"
	"writeln(b,a,c,d)\nelse if a < d then\nwriteln(b,a,d,c)\n"
	"else if b < d then\nwriteln(b,d,a,c)\nelse\nwriteln(d,b,a,c)\n"
	"else if b < c then\nif a < d then\nwriteln(b,c,a,d)\n"
	"else if c < d then\nwriteln(b,c,d,a)\nelse if b < d then\n"
	"writeln(b,d,c,a)\nelse\nwriteln(d,b,c,a)\nelse\nif a < d then\n"
	"writeln(c,b,a,d)\nelse if b < d then\nwriteln(c,b,d,a)\n"
	"else if c < d then\nwriteln(c,d,b,a)\nelse\nwriteln(d,c,b,a)\n"
	"end.\n" }
};

static int cases_left, cases_done;

static char set[16][16];
static int k, n, level;
static int stack[16];

static char prn_buf[4194304];

#define PRN(c) *prn_bufp++ = (c)

#define PRN_FLUSH() {write(1,prn_buf,(int)(prn_bufp-prn_buf));prn_bufp=prn_buf;}
#define PRN_CHKFLUSH() \
	if (((int)(prn_bufp - prn_buf)+1024) > sizeof(prn_buf)) PRN_FLUSH();

int main(void)
{
	register int i;
	register char *s, *r;
	register char *prn_bufp;

	prn_bufp = prn_buf;

	scanf("%d", &cases_left);
	cases_done = 0;

next_case:
	if (cases_left-- <= 0) {
		PRN_FLUSH();
		return 0;
	}
	scanf("%d", &n);

	if (cases_done++ != 0)
		PRN('\n');

	if (n <= NSIMPLE) {
		s = (char *)simple[n].s;

		if (((int)(prn_bufp - prn_buf) + simple[n].n + 1024) >= sizeof(prn_buf))
			PRN_FLUSH();

		while (*s)
			PRN(*s++);

		goto next_case;
	}

	s =	"program sort(input,output);\n"
		"var\n"
		"a";
	while (*s) PRN(*s++);
	for (i = 1; i < n; i++) { PRN(','); PRN('a'+i); }

	s =	" : integer;\n"
		"begin\n"
		"  readln(a";
	while (*s) PRN(*s++);
	for (i = 1; i < n; i++) { PRN(','); PRN('a'+i); }

	PRN(')'); PRN(';'); PRN('\n');

	/* --- main algorithm --- */

	/* memcpy(set[0], "abcdefghijklmno", 15); */
	for (s = set[0], i = 0; i < 15; i++)
		*s++ = 'a'+i;

	level = 1;
	stack[0] = 1;

iter:
	if (level == 0) {
		PRN('e'); PRN('n'); PRN('d'); PRN('.'); PRN('\n');
		goto next_case;
	}
	s = set[level-1];

	if (level == n) {
		PRN('w'); PRN('r'); PRN('i'); PRN('t'); PRN('e');
		PRN('l'); PRN('n'); PRN('(');

		PRN(s[0]);
		for (i = 1; i < n; i++) {
			PRN(',');
			PRN(s[i]);
		}
		PRN(')'); PRN('\n');

		level--;
		goto iter;
	}

	r = set[level];

	if ((k = stack[level - 1]) < 0) {
		level--;
		goto iter;
	}

	if (k > 0) {
		if (k != level) {
			PRN('e'); PRN('l'); PRN('s'); PRN('e'); PRN(' ');
		}

		PRN('i'); PRN('f'); PRN(' '); PRN(s[k-1]);
		PRN('<');
		PRN(s[level]); PRN(' ');
		PRN('t'); PRN('h'); PRN('e'); PRN('n'); PRN('\n');
	} else {
		PRN('e'); PRN('l'); PRN('s'); PRN('e'); PRN('\n');

		PRN_CHKFLUSH();
	}

	r[k] = s[level];
	for (i = 0; i < k; i++)
		*r++ = *s++;
	for (r++; i < level; i++)
		*r++ = *s++;
	for (i++,s++; i < n; i++)
		*r++ = *s++;

	stack[level - 1]--;
	stack[level] = level + 1;
	level++;
	goto iter;
}

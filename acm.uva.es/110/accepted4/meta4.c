#include <stdio.h>
#include <string.h>

#define ALLOW_PE   /* define to generate shorter output at the cost of P.E.*/

static const char *simple_cases[] = {
	NULL,	/* n = 0  (undefined) */

	/* n = 1 */
	"program sort(input,output);\nvar\na : integer;\nbegin\n  readln(a);\n"
	"writeln(a)\nend.\n",

	/* n = 2 */
	"program sort(input,output);\nvar\na,b : integer;\nbegin\n"
	"  readln(a,b);\nif a < b then\nwriteln(a,b)\nelse\nwriteln(b,a)\n"
	"end.\n",

	/* n = 3 */
	"program sort(input,output);\nvar\na,b,c : integer;\nbegin\n"
	"  readln(a,b,c);\nif a < b then\nif b < c then\nwriteln(a,b,c)\n"
	"else if a < c then\nwriteln(a,c,b)\nelse\nwriteln(c,a,b)\nelse\n"
	"if a < c then\nwriteln(b,a,c)\nelse if b < c then\nwriteln(b,c,a)\n"
	"else\nwriteln(c,b,a)\nend.\n"
};
#define MAX_SIMPLE_CASE 3

static int cases_left;

static char set[16][16];
static int k, n, level;
static int stack[16];

/* some black magic to reduce number of system calls needed */

static char prn_buf[65536];
#define PRN(c) *prn_bufp++ = (c)
#define PRN_CHKFLUSH() if (((int)(prn_bufp - prn_buf)+1024) > sizeof(prn_buf))\
			{ fwrite(prn_buf, 1, (int)(prn_bufp - prn_buf), stdout);\
			  prn_bufp=prn_buf; }
/* Note: CHKFLUSH is called after every "else\n",
    that's approx. 300-400 bytes of output between calls */

#define PRN_FLUSH() {fwrite(prn_buf,1,(int)(prn_bufp-prn_buf),stdout); prn_bufp=prn_buf;}

int main(void)
{
	register int i;
	register char *s, *r;
	register char *prn_bufp;

	prn_bufp = prn_buf;

	scanf("%d", &cases_left);

next_case:
	if (cases_left-- <= 0) {
		PRN_FLUSH();
		return 0;
	}
	scanf("%d", &n);

	/* check some simple cases */
	if (n <= MAX_SIMPLE_CASE) {
		s = (char *)simple_cases[n];
		i = strlen(s);

		if (((int)(prn_bufp - prn_buf) + i + 1024) >= sizeof(prn_buf)) {
			PRN_FLUSH();
			fwrite(s, 1, i, stdout);
		} else {
			while (*s)
				PRN(*s++);
		}

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
		if (cases_left > 0) PRN('\n');
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

		/* printf("if %c < %c then\n", s[k-1], s[level]); */
		PRN('i'); PRN('f'); PRN(' '); PRN(s[k-1]);
#ifdef ALLOW_PE
		PRN(' ');
#endif
		PRN('<');
#ifdef ALLOW_PE
		PRN(' ');
#endif
		PRN(s[level]); PRN(' ');
		PRN('t'); PRN('h'); PRN('e'); PRN('n');
		PRN('\n');
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

#include <stdio.h>
#include <string.h>

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

#define PRN_LASTFLUSH() fwrite(prn_buf, 1, (int)(prn_bufp - prn_buf), stdout);

static void meta(void)
{
	register int i;
	register char *s, *r;
	register char *prn_bufp;

	memcpy(set[0], "abcdefghijklmno", 15);
	prn_bufp = prn_buf;

	level = 1;
	stack[0] = 1;

iter:
	if (level == 0) {
		PRN_LASTFLUSH();
		return;
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
			/* printf("else "); */
			PRN('e'); PRN('l'); PRN('s'); PRN('e'); PRN(' ');
		}

		/* printf("if %c < %c then\n", s[k-1], s[level]); */
		PRN('i'); PRN('f'); PRN(' '); PRN(s[k-1]); PRN(' ');
		PRN('<'); PRN(' '); PRN(s[level]); PRN(' ');
		PRN('t'); PRN('h'); PRN('e'); PRN('n');
		PRN('\n');
	} else {
		/* printf("else\n"); */
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


int main(void)
{
	int m, i;

	scanf("%d", &m);
	while (m-- > 0) {
		scanf("%d", &n);

		printf(
			"program sort(input,output);\n"
			"var\n"
			"a"
		);
		for (i = 1; i < n; i++)
			printf(",%c", 'a'+i);
		printf(
			" : integer;\n"
			"begin\n"
			"  readln(a"
		);
		for (i = 1; i < n; i++)
			printf(",%c", 'a'+i);
		printf(");\n");

		meta();

		printf("end.\n");
		if (m != 0)
			printf("\n");
	}

	fflush(stdout);
	return 0;
}

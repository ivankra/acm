#include <stdio.h>
#include <string.h>

static char *indbuf="                                                        ";
#define INDENT(n) fwrite(indbuf, 1, (n), stdout)

static char set[16][16];
static int n;

static void meta(int level)
{
	register int i;
	register char *s = set[level-1], *r = set[level];
	int k;

	if (level >= n) {
		static char prn_buf[128];   /*to minimize number of fwrite()'s*/

		for (r = prn_buf, i = 2 * n; i-- > 0;)
			*r++ = ' ';
		*r++='w'; *r++='r'; *r++='i'; *r++='t'; *r++='e';
		*r++='l'; *r++='n'; *r++='('; *r++=s[0];
		for (i = 1; i < n; i++) {
			*r++ = ',';
			*r++ = s[i];
		}
		*r++=')'; *r++='\n';

		fwrite(prn_buf, 1, (int)(r - prn_buf), stdout);
		return;
	}

	for (k = level; k >= 0; k--) {
		INDENT(2*level);
		if (k == level)
			printf("if %c < %c then\n", s[k-1], s[level]);
		else if (k > 0)
			printf("else if %c < %c then\n", s[k-1], s[level]);
		else
			printf("else\n");

		for (i = 0; i < k; i++)
			r[i] = s[i];
		for (r[i] = s[level]; i < level; i++)
			r[i+1] = s[i];
		for (i++; i < n; i++)
			r[i] = s[i];
		
		for (r[i] = s[level]; i < n; i++)
			r[i+1] = s[i];

		meta(level + 1);
	}
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

		memcpy(set[0], "abcdefghijklmno", 15);
		meta(1);

		printf("end.\n");
		if (m != 0)
			printf("\n");
	}

	fflush(stdout);
	return 0;
}

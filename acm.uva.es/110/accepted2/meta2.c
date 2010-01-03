#include <stdio.h>
#include <string.h>

static char set[16][16];
static int k, n, level;
static int stack[16];
static char prn_buf[256]="writeln(";

static void meta(void)
{
	register int i;
	register char *s, *r;

	memcpy(set[0], "abcdefghijklmno", 15);

	level = 1;
	stack[0] = 1;

iter:
	if (level == 0)
		return;
	s = set[level-1];

	if (level == n) {
		r = prn_buf + 8;
		*r++ = s[0];
		for (i = 1; i < n; i++) {
			*r++ = ',';
			*r++ = s[i];
		}
		*r++=')'; *r++='\n';

		fwrite(prn_buf, 1, (int)(r - prn_buf), stdout);
		level--;
		goto iter;
	}

	r = set[level];

	if ((k = stack[level - 1]) < 0) {
		level--;
		goto iter;
	}

	if (k == level)
		printf("if %c < %c then\n", s[k-1], s[level]);
	else if (k > 0)
		printf("else if %c < %c then\n", s[k-1], s[level]);
	else
		printf("else\n");

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

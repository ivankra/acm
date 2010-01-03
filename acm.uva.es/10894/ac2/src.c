#include <stdio.h>
#include <stdlib.h>

int read(int, char *, int);
int write(int, char *, int);

char htext[] =
	"*****..***..*...*.*****...*...*.*****.*****.***...*****.*...*\n"
	"*.....*...*.*...*.*.......*...*.*...*...*...*..*..*...*..*.*.\n"
	"*****.*****.*...*.***.....*****.*****...*...*...*.*...*...*..\n"
	"....*.*...*..*.*..*.......*...*.*.*.....*...*..*..*...*...*..\n"
	"*****.*...*...*...*****...*...*.*..**.*****.***...*****...*..\n";

char vtext[] =
	"*****\n*....\n*****\n....*\n*****\n.....\n.***.\n*...*\n*****\n"
	"*...*\n*...*\n.....\n*...*\n*...*\n*...*\n.*.*.\n..*..\n.....\n"
	"*****\n*....\n***..\n*....\n*****\n.....\n.....\n.....\n*...*\n"
	"*...*\n*****\n*...*\n*...*\n.....\n*****\n*...*\n*****\n*.*..\n"
	"*..**\n.....\n*****\n..*..\n..*..\n..*..\n*****\n.....\n***..\n"
	"*..*.\n*...*\n*..*.\n***..\n.....\n*****\n*...*\n*...*\n*...*\n"
	"*****\n.....\n*...*\n.*.*.\n..*..\n..*..\n..*..\n";

int main()
{
	static char inbuf[65536], outbuf[30*1048576], t[65536];
	static int isdig[256], isdigm[256];
	char *p, *s, *inp, *outp;
	int i, j, n;

	for (n = '0'; n <= '9'; n++) isdig[n] = 1;
	for (n = '0'; n <= '9'; n++) isdigm[n] = 1; isdigm['-'] = 1;
	read(0, inp = inbuf, sizeof(inbuf));
	outp = outbuf;

	for (;;) {
		while (!isdigm[*inp]) inp++;

		if (*inp == '-') {
			inp++;
			for (n = *inp++ - '0'; isdig[*inp];) n = n * 10 + *inp++ - '0';
			s = vtext;
		} else {
			for (n = *inp++ - '0'; isdig[*inp];) n = n * 10 + *inp++ - '0';
			if (n == 0) break;
			s = htext;
		}

		for (; *s; s++) {
			for (p = t; *s != '\n';)
				for (j = *s++, i = 0; i < n; i++) *p++ = j;
			*p++ = '\n';
			*p = '\0';

			for (i = 0; i < n; i++)
				for (p = t; *p;) *outp++ = *p++;
		}

		*outp++ = '\n';
		*outp++ = '\n';
	}

	write(1, outbuf, outp - outbuf);
	exit(0);
}

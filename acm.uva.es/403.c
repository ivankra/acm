#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int write(int, char *, int);

static char big_font[] =
	".***..*...*.*****.*...*.*...*.****..*...*.****..*...*.****.."
	".****.*...*.*.....*......****.****..*...*.*...*.*...*.****.."
	"*****.*.....***...*.....*****.*****.*.....***...*.....*....."
	".****.*.....*..**.*...*..***..*...*.*...*.*****.*...*.*...*."
	"*****...*.....*.....*...*****...***....*.....*..*..*...**..."
	"*...*.*..*..***...*..*..*...*.*.....*.....*.....*.....*****."
	"*...*.**.**.*.*.*.*...*.*...*.*...*.**..*.*.*.*.*..**.*...*."
	".***..*...*.*...*.*...*..***..****..*...*.****..*.....*....."
	".***..*...*.*...*.*..**..****.****..*...*.****..*..*..*...*."
	".****.*......***......*.****..*****.*.*.*...*.....*....***.."
	"*...*.*...*.*...*.*...*..***..*...*.*...*..*.*...*.*....*..."
	"*...*.*...*.*.*.*.**.**.*...*.*...*..*.*....*....*.*..*...*."
	"*...*..*.*....*.....*.....*...*****....*....*....*....*****."
	"..............................";
#define BIGFONT(n,r,c) big_font[((n) * 30) + ((r) * 6) + (c)]

static char page[64][64];

int main()
{
	static char buf[8192], cmd, arg[8][256], text[256];
	int c, i, j, k, m, row, col, fontw, len;
	char *p;

	memset(page, '.', sizeof(page));

	while (gets(buf)) {
		for (p = buf, i = 0; i < 8; i++)
			arg[i][0] = '\0';

		for (k = 0, len = -1; k < 8 && *p;) {
			while (*p && isspace(*p)) p++;
			if (*p == '\0') break;

			if (*p != '|') {
				for (i = 0; *p && !isspace(*p);)
					arg[k][i++] = *p++;
				arg[k++][i] = '\0';
				continue;
			}

			for (i = 0, p++; *p && *p != '|';)
				text[i++] = *p++;
			len = i;
			text[i] = '\0';
			break;
		}

		if (k < 1)
			continue;

		for (p = arg[0]; !isalpha(*p); p++);
		if (*p == '\0') continue;

		cmd = toupper(*p);

		if (cmd == 'E') {
			for (p = buf, i = 0; i < 60; i++) {
				for (k = 0; k < 60; k++)
					*p++ = page[i][k];
				*p++ = '\n';
			}

			for (*p++ = '\n', i = 0; i < 60; i++)
				*p++ = '-';
			*p++ = '\n';
			*p++ = '\n';

			write(1, buf, p - buf);

			memset(page, '.', sizeof(page));
			continue;
		}

		if (len < 0)
			continue;

		for (p = arg[1]; *p && *p != '5'; p++);
		fontw = (*p == '5') ? 6 : 1;

		row = atoi(arg[2]) - 1;
		if (row < 0) row = 0;

		if (cmd == 'P')
			col = atoi(arg[3]) - 1;
		else if (cmd == 'L')
			col = 0;
		else if (cmd == 'R')
			col = 60 - len * fontw;
		else if (cmd == 'C')
			col = 30 - ((len * fontw) / 2);
		else
			continue;

		if (row >= 60) continue;

		if (fontw == 1) {
			if (row < 0) continue;

			if (col < 0) {
				i = -col;
				col = 0;
			} else {
				i = 0;
			}

			for (; i < len && col < 60; i++, col++)
				if (text[i] != ' ')
					page[row][col] = text[i];
			continue;
		}

		for (i = 0; i < len; i++) {
			if (!isalpha(text[i])) {
				col += 6;
				continue;
			}

			c = toupper(text[i]) - 'A';
				
			for (j = 0; j < 6 && col < 60; j++, col++) {
				if (col < 0)
					continue;

				for (k=0, m = row; k < 5 && m < 60; k++, m++) {
					if (BIGFONT(c, k, j) == '*')
						page[m][col] = '*';
				}
			}
		}
	}

	return 0;
}

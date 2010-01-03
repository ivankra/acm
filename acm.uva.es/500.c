#include <stdio.h>
#include <string.h>
#include <assert.h>

int type[128], len[128], width[128], n, cols;
char *C[128][1024], linebuf[128][1024];

int max(int a, int b) { return (a > b) ? a : b; }

void parse(unsigned char *s)
{
	unsigned char *q;

for (q = s; *q; q++)
  if (*q == '\t') { for(;;)malloc(10000); }

	while (*s == ' ' || *s == '\t') s++;

	len[n] = 0;
	if (*s == 218) {
		type[n] = 's';
		C[n][0] = "\xDA";
		C[n][1] = "\xC2";
		C[n][2] = "\xBF";
	} else if (*s == 195) {
		type[n] = 's';
		C[n][0] = "\xC3";
		C[n][1] = "\xC5";
		C[n][2] = "\xB4";
	} else if (*s == 192) {
		type[n] = 's';
		C[n][0] = "\xC0";
		C[n][1] = "\xC1";
		C[n][2] = "\xD9";
	} else {
		assert(*s == 179);
		s++;
		type[n] = 't';
		strcpy((char *)linebuf[n], (char *)s);
		s = (unsigned char *)linebuf[n];
		for (len[n] = 0;;) {
			while (*s == ' ' || *s == '\t') s++;
			if (*s == '\0') break;
			C[n][len[n]] = (char *)s;
			while (*s && *s != 179) s++;
			if (*s != 179) break;
			for (q = s; (char *)q > C[n][len[n]]; q--)
				if (q[-1] != ' ' && q[-1] != '\t') break;
			*q = '\0';
			*s++ = '\0';
			len[n]++;
		}
		return;
	}
}

int main()
{
	static char buf[65536];
	int i, j, k, t;

	while (gets(buf) && sscanf(buf, "%d", &t) != 1);
	gets(buf);

	while (t-- > 0) {
		memset(width, 0, sizeof(width));

		for (n = 0; gets(buf); n++) {
			for (i = 0; buf[i] && buf[i] != '\n' && buf[i] != '\r'; i++);
			buf[i] = '\0';
			if (i == 0) break;
			assert(n < 125);
			parse((unsigned char *)buf);
		}

		cols = -1;
		for (i = 0; i < n; i++) {
			if (type[i] == 's') continue;
			if (cols < 0) cols = len[i];
			assert(cols == len[i]);
		}

		for (i = 0; i < n; i++) {
			if (type[i] == 's') continue;
			for (j = 0; j < cols; j++)
				width[j] = max(width[j], strlen(C[i][j]));
		}

		for (i = 0; i < n; i++) {
			if (type[i] == 's') {
				for (j = 0; j < cols; j++) {
					printf("%s\xC4", C[i][j ? 1 : 0]);
					for (k = 0; k < width[j]; k++)
						printf("\xC4");
					printf("\xC4");					
				}
				printf("%s\n", C[i][2]);
				continue;
			}

/*			for (j = 0; j < cols; j++)
				if (C[i][j][0] != '\0') break;
			assert(j < cols);
*/
			for (j = 0; j < cols; j++)
				printf("\xB3 %-*s ", width[j], C[i][j]);
			printf("\xB3\n");
		}

		if (t) printf("\n");
	}

	return 0;
}

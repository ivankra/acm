#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NMEM	32768
#define NCODE	131072

unsigned char C[NCODE], src[NCODE], hl[NCODE];
unsigned arg[NCODE], list[NCODE], srcp[NCODE], mp, cp, cn, sn;

int M[NMEM];

void err(int i, char *s)
{
	printf("%s\n", s);
	if (i) {
		printf("\n");
		for (i = 0; i < sn; i++) {
			if (hl[i] == 1) printf("\033[05;01;41m");
			if (hl[i] == 2) printf("\033[01;33m");
			putchar(src[i]);
			if (hl[i]) printf("\033[0m");
		}
	}
	exit(1);
}

int main(int argc, char *argv[])
{
	int i, c;
	FILE *fp;

	if (argc != 2) err(0, "Please specify filename in command line.");

	fp = fopen(argv[1], "r");
	if (fp == NULL) err(0, "Can't open specified file.");

	for (cn = sn = 0; (c = getc(fp)) != EOF; sn++) {
		if (sn+2 > NCODE) err(0, "Code size limit exceeded.");
		src[sn] = c; hl[sn] = 0;
		if (strchr("<>+-.,[]", c)) {
			hl[sn] = 2; srcp[cn] = sn; C[cn] = c; cn++;
		}
	}

	fclose(fp);

	for (i = c = 0; i < cn; i++) {
		if (C[i] == '[') {
			list[c++] = i;
		} else if (C[i] == ']') {
			if (c-- == 0) {
				hl[srcp[i]] = 1;
				err(1, "No matching '['.");
			}
			arg[list[c]] = i+1;
			arg[i] = list[c];
		}
	}

	if (c != 0) {
		for (i = 0; i < c; i++) hl[srcp[list[i]]] = 1;
		err(1, "No matching ']'.");
	}

	C[cn] = C[cn+1] = 0;
	for (i = 0; i < cn;) {
		if (C[i] == '[' || C[i] == ']') { i++; continue; }
//		for (c = 1; C[i+c] == C[i]; c++);
c=1;		arg[i] = c;
		i += c;
	}

	memset(M, 0, sizeof(M));
	mp = cp = 0;

	while (cp < cn) {
		switch (C[cp]) {
			case '>':
				mp = (mp + arg[cp]) % NMEM;
				cp += arg[cp];
				break;
			case '<':
				mp = (mp + NMEM - (arg[cp] % NMEM)) % NMEM;
				cp += arg[cp];
				break;
			case '+':
				M[mp] += arg[cp];
				cp += arg[cp];
				break;
			case '-':
				M[mp] -= arg[cp];
				if (M[mp] < -1000) {
					hl[srcp[cp]] = 1;
					err(1,"underflow");
				}
				cp += arg[cp];
				break;
			case '.':
				for (i = 0; i < arg[cp]; i++) putchar(M[mp]);
				cp += arg[cp];
				break;
			case ',':
				for (i = 0; i < arg[cp]; i++) M[mp]=getchar();
				cp += arg[cp];
				break;
			case '[':
				cp = M[mp] ? (cp+1) : arg[cp];
				break;
			case ']':
				cp = M[mp] ? arg[cp] : (cp+1);
				break;
		}
	}

	return 0;
}

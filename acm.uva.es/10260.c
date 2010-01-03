#include <stdio.h>

int main()
{
	static char buf[1024], out[1024], tab[256];
	int i, j, l, c;

	for (i = 0; i < 256; i++) tab[i] = 0;
	for (i = 0; j = "BFPVbfpv"[i]; i++) tab[j] = '1';
	for (i = 0; j = "CGJKQSXZcgjkqsxz"[i]; i++) tab[j] = '2';
	for (i = 0; j = "DTdt"[i]; i++) tab[j] = '3';
	for (i = 0; j = "Ll"[i]; i++) tab[j] = '4';
	for (i = 0; j = "MNmn"[i]; i++) tab[j] = '5';
	for (i = 0; j = "Rr"[i]; i++) tab[j] = '6';

	while (gets(buf)) {
		for (i = 0, j = 0, l = 0; buf[i]; i++) {
			c = tab[(unsigned)buf[i]];
			if (c == 0) {
				l = 0;
			} else if (l != c) {
				out[j++] = c;
				l = c;
			}
		}
		out[j++] = '\n';

		fwrite(out, 1, j, stdout);
	}

	return 0;
}

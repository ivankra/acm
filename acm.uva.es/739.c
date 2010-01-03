#include <stdio.h>

int main()
{
	static char buf[256], r[16];
	static int code[256];
	register char *p;
	register int i, k;

	printf("%9s%-25sSOUNDEX CODE\n", "", "NAME");

	for (i = 0; i < 256; i++) code[i] = 0;
	for (p = "BPFV"; *p; p++) code[*p] = 1;
	for (p = "CSKGJQXZ"; *p; p++) code[*p] = 2;
	code['D'] = code['T'] = 3;
	code['L'] = 4;
	code['M'] = code['N'] = 5;
	code['R'] = 6;

	while (gets(buf)) {
		for (p = buf; *p && (*p < 'A' || *p > 'Z'); p++);
		if (*p == '\0') continue;

		r[0] = *p++;

		for (k = code[r[0]], i = 1; *p && i < 4; p++) {
			if (code[*p] == 0)
				k = 0;
			else if (code[*p] != k)
				r[i++] = '0' + (k = code[*p]);
		}

		while (i < 4)
			r[i++] = '0';
		r[i] = '\0';

		printf("         %-25s%s\n", buf, r);
	}

	printf("                   END OF OUTPUT\n");

	return 0;
}

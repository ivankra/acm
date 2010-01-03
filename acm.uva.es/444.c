#include <stdio.h>

int main()
{
	static char line[4096], buf[4096], isdig[256], isval[256];
	int i, c, k;
	char *p, *q;

	for (i = 0; i < 256; i++) {
		isdig[i] = (i >= '0' && i <= '9');
		isval[i] = (i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z');
	}

	for (p = " !,.:;?"; *p;)
		isval[*p++] = 1;

	while (gets(line)) {
		for (p = line; *p; p++);

		for (p--, q = line; q < p;) {
			i = *p;
			*p-- = *q;
			*q++ = i;
		}

		for (p = line, q = buf; *p; p++) {
			if (isval[*p]) {
				for (k = *p; k > 0; k /= 10)
					*q++ = (k % 10) + '0';
			} else if (isdig[*p]) {
				break;
			}
		}

		if (!isdig[*p]) {
			*q++ = '\n';
			fwrite(buf, 1, q - buf, stdout);
			continue;
		}

		for (p = line, q = buf, k = 0, c = 0; *p; p++) {
			if (!isdig[*p])
				continue;

			if (c == 0) {
				if (*p == '1') {
					k = 1;
					c = 1;
				} else {
					k = *p - '0';
					c = 2;
				}
			} else {
				k = k * 10 + *p - '0';

				if (++c == 3) {
					*q++ = k;
					c = 0;
				}
			}
		}

		*q++ = '\n';
		fwrite(buf, 1, q - buf, stdout);
	}

	return 0;
}

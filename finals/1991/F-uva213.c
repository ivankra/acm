#include <stdio.h>

int write(int, char *, int);

int main()
{
	static char hdr[1024], outbuf[16384];
	int i, c, k, m;
	char *outp;

	for (outp = outbuf; gets(hdr);) {
		for (;;) {
			for (i = 0, k = 0; i < 3 && (c = getchar()) != EOF;)
				if (c == '0' || c == '1') {
					k = (k << 1) | (c - '0');
					i++;
				}

			if (i < 3 || k == 0)
				break;

			for (;;) {
				for (i=0, m=0; i<k && (c=getchar()) != EOF;) {
					if (c == '0' || c == '1') {
						m = (m << 1) | (c - '0');
						i++;
					}
				}

				if ((m + 1) >= (1 << k))
					break;

				m += (1 << k) - k - 1;
				*outp++ = hdr[m];

				if ((outp - outbuf) > (sizeof(outbuf) - 16)) {
					write(1, outbuf, outp - outbuf);
					outp = outbuf;
				}
			}
		}
		*outp++ = '\n';

		while ((c = getchar()) != EOF && c != '\n');
	}

	if (outp != outbuf)
		write(1, outbuf, outp - outbuf);

	return 0;
}

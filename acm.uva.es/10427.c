#include <stdio.h>

int main()
{
	static int n, tpow[] = {
		1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
		100000000, 1000000000
	};
	static char outbuf[65536];
	register char *outp;

	outp = outbuf;

	while (scanf("%d", &n) == 1) {
		if (n <= 9)
			*outp++ = n + '0';
		else if (n <= 189)
			*outp++ = ((((n + 10) >> 1) / tpow[1 - ((n + 10) & 1)]) % 10) + '0';
		else if (n <= 2889)
			*outp++ = ((((n + 110) / 3) / tpow[2 - ((n + 110) % 3)]) % 10) + '0';
		else if (n <= 38889)
			*outp++ = ((((n + 1110) >> 2) / tpow[3 - ((n + 1110) & 3)]) % 10) + '0';
		else if (n <= 488889)
			*outp++ = ((((n + 11110) / 5) / tpow[4 - ((n + 11110) % 5)]) % 10) + '0';
		else if (n <= 5888889)
			*outp++ = ((((n + 111110) / 6) / tpow[5 - ((n + 111110) % 6)]) % 10) + '0';
		else if (n <= 68888889)
			*outp++ = ((((n + 1111110) / 7) / tpow[6 - ((n + 1111110) % 7)]) % 10) + '0';
		else
			*outp++ = ((((n + 11111110) >> 3) / tpow[7 - ((n + 11111110) & 7)]) % 10) + '0';
		*outp++ = '\n';
	}

	write(1, outbuf, outp - outbuf);

	return 0;
}

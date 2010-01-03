int read(int, char *, int);
int write(int, const char *, int);

int main()
{
	static char inbuf[16384+1], outbuf[16384];
	static char hex[] = "0123456789ABCDEF";
	register unsigned long r;
	register char *outp, *inp, *inmax;

	for (r = 0, outp = outbuf;;) {
		inmax = inbuf + read(0, inbuf, sizeof(inbuf)-1);
		if (inmax <= inbuf)
			break;

		if (r == 0 && *inbuf == '#')
			break;

		for (inp = inbuf; inp < inmax;) {
			if (*inp == '\n') {
				r = (34943 - ((r << 16) % 34943)) % 34943;
				*outp++ = hex[r >> 12];
				*outp++ = hex[(r >> 8) & 15];
				*outp++ = ' ';
				*outp++ = hex[(r >> 4) & 15];
				*outp++ = hex[r & 15];
				*outp++ = '\n';

				if ((outp + 16) > &outbuf[sizeof(outbuf)]) {
					write(1, outbuf, outp - outbuf);
					outp = outbuf;
				}

				if (*++inp == '#')
					break;

				r = 0;
			} else {
				r = ((r << 8) + (unsigned)*inp++) % 34943;
			}

		}
	}

	if (outp != outbuf)
		write(1, outbuf, outp - outbuf);

	return 0;
}

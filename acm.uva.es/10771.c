int read(int, unsigned char *, int);
int write(int, unsigned char *, int);

static unsigned isdig[256];

int main()
{
	static unsigned char inbuf[4*1048576], outbuf[4*1048576];
	register unsigned char *inp, *outp;
	register unsigned i;

	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	read(0, inp = inbuf, sizeof(inbuf));
	outp = outbuf;

	for (;;) {
		while (!isdig[*inp]) inp++;
		while (isdig[*inp]) inp++;

		while (!isdig[*inp]) inp++;
		for (i = 0; isdig[*inp];)
			i = i * 10 + *inp++ - '0';

		while (!isdig[*inp]) inp++;
		while (*inp == '0') inp++;
		if (!isdig[*inp]) break;
		while (isdig[*inp]) inp++;

		if (i & 1) {
			*(unsigned long *)outp = 0x616B654B; outp += 4;
			*outp++ = '\n';
		} else {
			*(unsigned long *)outp = 0x65726147; outp += 4;
			*(unsigned long *)outp = 0x00000A64; outp += 2;
		}
	}

	write(1, outbuf, outp - outbuf);
	return 0;
}

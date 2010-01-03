int read(int, unsigned char *, int);
int write(int, const unsigned char *, int);

static int modexp(int b, int e, int m)
{
	register int r;

	for (r = 1; e > 0; e >>= 1) {
		if (e & 1)
			r = (int)(((long long)r * (long long)b) % (long long)m);

		b = (int)(((long long)b * (long long)b) % (long long)m);
	}

	return r;
}

static int isdig[256], isdigm[256];

void mktab()
{
	register int i;

	for (i = 0; i < 256; i++) isdig[i] = 0;
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	for (i = 0; i < 256; i++) isdigm[i] = isdig[i];
	isdigm['-'] = 1;
}

int main()
{
	static unsigned char inbuf[1048576], outbuf[1048576];
	static int a, p;
	register unsigned char *inp, *outp;

	mktab();

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = '-';
	outp = outbuf;

#define READ(var) \
{ \
	while (!isdigm[*inp]) inp++; \
	if (*inp == '-') goto ex; \
	for (var = *inp++ - '0'; isdig[*inp];) \
		var = var * 10 + *inp++ - '0'; \
}

	for (;;) {
		READ(a);
		READ(p);

		a %= p;

		if (a <= 1 || p <= 2 || modexp(a, (p - 1) / 2, p) == 1) {
			*(unsigned long *)outp = *(unsigned long *)("Yes\n");
			outp += 4;
		} else {
			*outp++ = 'N'; *outp++ = 'o'; *outp++ = '\n';
		}
	}

ex:	write(1, outbuf, outp - outbuf);
	return 0;
}

int read(int, unsigned char *, unsigned);
int write(int, const unsigned char *, unsigned);

static unsigned legendre_d(unsigned a, unsigned p)
{
	static unsigned marked_3_5[8] = { 0, 0, 0, 1, 0, 1, 0, 0 };
	register unsigned k, r;

	for (r = 1;;) {
		if (a <= 1)
			return r;

		for (k = 0; (a & 1) == 0; k ^= 1, a >>= 1);

		if (k && marked_3_5[p & 7])
			r ^= 1;

		if ((p & 3) == 3 && (a & 3) == 3)
			r ^= 1;

		if (a == 1)
			return r;

		k = a;
		a = p % a;
		p = k;
	}
}

static unsigned isdig[256], isdigm[256];

static void mktab()
{
	register unsigned i;

	for (i = 0; i < 256; i++) isdig[i] = 0;
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	for (i = 0; i < 256; i++) isdigm[i] = isdig[i];
	isdigm['-'] = 1;
}

int main()
{
	static unsigned char inbuf[1048576], outbuf[1048576];
	register unsigned a, p;
	register unsigned char *inp, *outp;

	mktab();

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = '-';
	outp = outbuf;

#define READ(var) { \
	while (!isdigm[*inp]) inp++; \
	if (*inp == '-') goto ex; \
	for (var = *inp++ - '0'; isdig[*inp];) \
		var = var * 10 + *inp++ - '0'; \
}

	for (;;) {
		READ(a);
		READ(p);

		a %= p;

		if (a <= 1 || p <= 2 || legendre_d(a, p)) {
			*(unsigned long *)outp = *(unsigned long *)("Yes\n");
			outp += 4;
		} else {
			*(unsigned long *)outp = *(unsigned long *)("No\n ");
			outp += 3;
		}
	}

ex:	write(1, outbuf, outp - outbuf);
	return 0;
}

int read(int, unsigned char *, int);
int write(int, const unsigned char *, int);

static int legendre(int a, int p)
{
	register int k, r;

	for (r = 1;;) {
		if (a <= 1) return (r * a);

		for (k = 0; (a & 1) == 0; k++, a >>= 1);

		if ((k & 1) && ((p & 7) == 3 || (p & 7) == 5))
			r = -r;

		if ((p & 3) == 3 && (a & 3) == 3)
			r = -r;

		if (a == 1)
			return r;

		k = a;
		a = p % a;
		p = k;
	}
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

		if (a <= 1 || p <= 2 || legendre(a, p) == 1) {
			*(unsigned long *)outp = *(unsigned long *)("Yes\n");
			outp += 4;
		} else {
			*outp++ = 'N'; *outp++ = 'o'; *outp++ = '\n';
		}
	}

ex:	write(1, outbuf, outp - outbuf);
	return 0;
}

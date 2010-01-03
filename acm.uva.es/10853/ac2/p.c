int read(int, unsigned char *, unsigned);
int write(int, const unsigned char *, unsigned);

static long long len, amin, amax, bmin, bmax;

static int solve()
{
	register long long d, q;

	if (len-- <= amax)
		return 'A';

	d = amax - amin + bmin - bmax;
	q = len / (amin + bmax);

	if (d < 0 && q > ((bmax - bmin - amax + d + 1) / d))
		return 'B';

	return ((len % (amin + bmax)) < (amax + q * d)) ? 'A' : 'B';
}

int main()
{
	static unsigned char inbuf[131072], outbuf[65536];
	static unsigned isdig[256];
	static int t;
	register unsigned char *inp, *outp;
	register int i;

/****	for (i = 0; i < 256; i++) isdig[i] = 0;*/
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = 0;
	outp = outbuf;

#define READ(var) \
	{ while (!isdig[*inp]) inp++; \
	  for (i=(*inp++)-'0';isdig[*inp];) i=i*10+(*inp++)-'0'; var=i; }

	READ(t);

	while (t-- > 0) {
		READ(len); READ(amin); READ(amax); READ(bmin); READ(bmax);

		*outp++ = solve();
		*outp++ = '\n';
	}

	write(1, outbuf, outp - outbuf);
	return 0;
}

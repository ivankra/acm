int read(int, unsigned char *, unsigned);
int write(int, const unsigned char *, unsigned);

static unsigned isdig[256], isdigz[256];

static void mktab()
{
	register unsigned i;

	for (i = 0; i < 256; i++) isdig[i] = 0;
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	for (i = 0; i < 256; i++) isdigz[i] = isdig[i];
	isdigz['-'] = 1;
}

int main()
{
	static unsigned char inbuf[1048576], outbuf[1048576];
	register unsigned char *inp, *outp;
	int x0, y0, x1, y1;
	static int n, s, t;

	mktab();

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = 0;
	outp = outbuf;

#define READ(var) { \
	while (!isdigz[*inp]) inp++; \
	for (var = *inp++ - '0'; isdig[*inp];) \
		var = var * 10 + *inp++ - '0'; \
}
	READ(t);

	while (t-- > 0) {
		READ(s); READ(n);

		while (s-- > 0) {
			READ(y0); READ(x0); READ(y1); READ(x1);

			if (((x0 + y0) & 1) != ((x1 + y1) & 1)) {
				/* no move */
				/* 6E 6F 20 6D . 6F 76 65 0A*/
				*(unsigned long *)outp = 0x6D206F6E; outp += 4;
				*(unsigned long *)outp = 0x0A65766F; outp += 4;
			} else if (y0 == y1 && x0 == x1) {
				*(unsigned short *)outp = 0x0A30; outp += 2;
			} else {
				y1 -= y0;
				if (y1 < 0) y1 = -y1;

				x1 -= x0;
				if (x1 < 0) x1 = -x1;

				if (y1 == x1) {
					*(unsigned short *)outp = 0x0A31; outp += 2;
				} else {
					*(unsigned short *)outp = 0x0A32; outp += 2;
				}
			}
		}
	}

ex:	write(1, outbuf, outp - outbuf);
	return 0;
}

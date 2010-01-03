#include <stdio.h>
#include <string.h>

int read(int, unsigned char *, unsigned);

static int p, pat[2048], npat, npat2, pmask, pmsb;
static long long tabbuf1[2048], tabbuf2[2048];
static unsigned char inbuf[2*65536];
static int isdig[256], isdigz[256], isht[256], htmap[256];

static void mktab(void)
{
	register int i;

	for (i = 0; i < 256; i++) isdig[i] = 0;
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	for (i = 0; i < 256; i++) isdigz[i] = 0;
	for (i = '0'; i <= '9'; i++) isdigz[i] = 1;
	isdigz[0] = 1;

	for (i = 0; i < 256; i++) isht[i] = 0;
	isht['H']=1;
	isht['T']=1;
	isht['h']=1;
	isht['t']=1;

	htmap['H']=1;
	htmap['h']=1;
	htmap['T']=0;
	htmap['t']=0;
}

static const char *pw2[] = {
	"1", "2", "4", "8", "16", "32", "64", "128", "256", "512", "1024",
	"2048", "4096", "8192", "16384", "32768", "65536", "131072", "262144",
	"524288", "1048576", "2097152", "4194304", "8388608", "16777216",
	"33554432", "67108864", "134217728", "268435456", "536870912",
	"1073741824", "2147483648", "4294967296", "8589934592", "17179869184",
	"34359738368", "68719476736", "137438953472", "274877906944",
	"549755813888", "1099511627776", "2199023255552", "4398046511104",
	"8796093022208", "17592186044416", "35184372088832", "70368744177664",
	"140737488355328", "281474976710656", "562949953421312",
	"1125899906842624", "2251799813685248", "4503599627370496",
	"9007199254740992", "18014398509481984", "36028797018963968",
	"72057594037927936", "144115188075855872", "288230376151711744",
	"576460752303423488", "1152921504606846976", "2305843009213693952",
	"4611686018427387904", "9223372036854775808", "18446744073709551616"
};

int main(void)
{
	static int t;
	register int i, k, n;
	register long long *tab, *tabnext;
	register unsigned char *inptr;
	long long r1;

	mktab();

	inbuf[read(0, inptr = inbuf, sizeof(inbuf))] = 0;

#define READINT(var) { \
	while (!isdigz[*inptr]) inptr++; \
	if (*inptr == 0) goto ex; \
	for (var = *inptr++ - '0'; isdig[*inptr];) \
		var = var * 10 + *inptr++ - '0'; \
}

	for (t = 1;; t++) {
		READINT(n);
		if (n == 0) break;

		READINT(npat);

		npat2 = npat;
		for (p = 0; npat2-- > 0;) {
			while (!isht[*inptr]) inptr++;

			for (i = 0, k = 0; isht[*inptr]; i++)
				k = (k << 1) | htmap[*inptr++];

			p = i;
			pat[npat2] = k;
		}

		if (p > n || npat == 0) {
			printf("Case %d: 1/1\n", t);
			continue;
		}

		pmask = (1 << p) - 1;
		pmsb = (1 << (p - 1));

		tab = tabbuf1;
		tabnext = tabbuf2;

		for (i = 0; i <= pmask; i++)
			tab[i] = 1;

		for (i = 0; i < npat; i++)
			tab[pat[i]] = 0;

		for (k = p + 1; k <= n; k++) {
			for (i = 0; i <= pmask; i++)
				tabnext[i] = tab[i>>1] + tab[(i>>1) | pmsb];

			for (i = 0; i < npat; i++)
				tabnext[pat[i]] = 0;

			tab = tabnext;
			tabnext = (tabnext == tabbuf1) ? tabbuf2 : tabbuf1;
		}

		for (i = 0, r1 = 0; i <= pmask; i++)
			r1 += tab[i];

		if (r1 == 0) {
			printf("Case %d: 0\n", t);
		} else {
			while (n > 0 && ((unsigned)r1 & 1) == 0) {
				n--;
				r1 >>= 1;
			}

			printf("Case %d: %lld/%s\n", t, r1, pw2[n]);
		}
	}
ex:
	return 0;
}

#include <stdio.h>
#include <string.h>

static int n, p, pat[2048], npat, npat2, pmask, pmsb;
static long long tabbuf1[2048], tabbuf2[2048];

int main()
{
	static char s[256];
	static int t;
	register int i, k;
	register long long *tab, *tabnext;
	long long r1, r2;

	for (t = 1; scanf("%d %d", &n, &npat) == 2 && n > 0; t++) {

		npat2 = npat;
		for (p = 0; npat2-- > 0 && scanf(" %[HTht]", s) == 1;) {
			for (i = 0, k = 0; s[i]; i++)
				if ((s[i] | 0x20) == 'h')
					k = (k << 1) | 1;
				else
					k <<= 1;

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

		for (tab[0] = 1, i = 1; i <= pmask; i++)
			tab[i] = 0;

		for (k = 1; k <= n; k++) {
			for (i = 0; i <= pmask; i++)
				tabnext[i] = tab[i>>1] + tab[(i>>1) | pmsb];

			if (k >= p) {
				for (i = 0; i < npat; i++)
					tabnext[pat[i]] = 0;
			}

			tab = tabnext;
			tabnext = (tabnext == tabbuf1) ? tabbuf2 : tabbuf1;
		}

		for (i = 0, r1 = 0; i <= pmask; i++)
			r1 += tab[i];

		if (r1 == 0) {
			printf("Case %d: 0\n", t);
		} else {
			r2 = (1ULL << n);

			while (r2 > 1ULL && (r1 & 1ULL) == 0ULL)
				r2 >>= 1, r1 >>= 1;

			printf("Case %d: %lld/%lld\n", t, r1, r2);
		}
	}

	return 0;
}

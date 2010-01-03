#include <stdio.h>
#include <string.h>
#include <assert.h>

#define GET(a,k) (((a)[(k)>>5]>>((k)&31))&1)
#define SET(a,k) (a)[(k)>>5]|=1U<<((k)&31)

unsigned seen[1<<16], outs[1<<18], oute[32];
int st[(1<<21)+10], n, m, outp, mask;

void euler() {
	memset(seen, 0, sizeof(seen));
	mask = (1<<(n-1)) - 1;
	st[0] = 0; m = 1;
	while (m > 0) {
		int x = st[m-1];

		if (x < 0) {
			if (x == -'1') SET(outs, outp);
			outp++;
			m--;
			continue;
		}

		if (x & 1)
			st[m-1] = -(((x >> 1) & 1) + '0');
		else
			st[m-1]++;

		if (GET(seen, x) == 0) {
			SET(seen, x);
			st[m++] = (x & mask) << 1;
		}
	}
	outp += n-2;
}

int main()
{
	memset(outs, 0, sizeof(outs));
	outp = 0;
	for (n = 2; n <= 21; n++) {
		outp += 16;
		euler();
		oute[n] = outp;
	}

	int k, t;
	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &k) == 2;) {
		k &= (1 << n) - 1;
		if (n <= 1) { printf("%c\n", "01"[k]); continue; }

		int r = 0;
		for (int i = 0; i < n; i++, k++) {
			k &= (1 << n) - 1;
			r = (r << 1) + GET(outs, oute[n]-1-k);
		}
		printf("%d\n", r);
	}

	return 0;
}

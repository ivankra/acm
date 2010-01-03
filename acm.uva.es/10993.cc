#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define MAXL 2400

unsigned Xcan[MAXL][3126];

#define GET(a,k) ((a[(k)>>5] >> ((k)&31)) & 1)
#define SET(a,k) a[(k)>>5] |= 1U << ((k)&31)

int allowed[16], dig[16], n, L;

//#define Dprintf printf
void Dprintf(...) {}

int one_solver() {
	Dprintf("one_solver  ");

	int x = 0, d;

	for (d = 0; !allowed[d]; d++);
	if (d == 0) return 0;

	for (L = 1;; L++) {
		if (L > n+10) return 0;

		x = (x * 10 + d) % n;
		if (x == 0) break;
	}

	for (int i = 0; i < L; i++)
		putchar(d+'0');
	putchar('\n');
	return 1;
}

int solve() {
	int tens[MAXL+1], t = 1;

	{ int cnt=0;
	  for(int i = 0; i <= 9; i++) if (allowed[i]) cnt++;
	  if (cnt==0) return 0;
	  if (cnt==1) return one_solver(); }

	{ int w[16]; memset(w,0,sizeof(w));
	  for (int b = 1; b <= 10; b++) w[(((n%10)*b)%10)] = 1;
	  int k; for (k = 0; k <= 9; k++) if (w[k] && allowed[k]) break;
	  if (k >= 10) return 0; }

	for (int i = 0; i < 3126; i++) Xcan[0][i] = 0;
	SET(Xcan[0], 0);

	for (L = 1;; L++) {
		tens[L-1] = t;
		if (L >= MAXL) {
			Dprintf("exhaust ");
			return 0;
		}

		int b = ((n/32+2) <? 3126);
		for (int i = 0; i < b; i++) Xcan[L][i] = 0;

		int cnt=0;
		for (int r = 0; r < n; r++) {
			if (GET(Xcan[L-1], r) == 0) continue;
			cnt++;
			for (int i = 0; dig[i] >= 0; i++) {
				int r1 = (r + dig[i] * t) % n;
				SET(Xcan[L], r1);
				if (r1 == 0 && dig[i] != 0) goto ok;
			}
		}
		if (cnt == 0) {
			Dprintf("[no rem at L=%d] ",L);
			return 0;
		}
		t = (t * 10) % n;
	}

ok:
	for (int r = 0, d0 = 1; L > 0; L--, d0 = 0) {
		int d, r1=0;
		assert(0 <= r && r < n && GET(Xcan[L],r));
		for (d = d0; d <= 9; d++) {
			r1 = (r - d * tens[L-1] + 10*n) % n;
			if (allowed[d] && GET(Xcan[L-1], r1)) break;
		}
		putchar(d+'0');
		r = r1;
	}
	printf("\n");
	return 1;
}

int main()
{
	char s[16];
	while (scanf(" %s %d", s, &n) == 2 && n > 0) {
		assert(1 <= n && n <= 100000);

		int i;
		for (i = 0; s[i] && isdigit(s[i]); i++) dig[i] = s[i]-'0';
		dig[i] = -1;

		memset(allowed, 0, sizeof(allowed));
		for (i = 0; dig[i] >= 0; i++)
			allowed[dig[i]] = 1;

		if (solve() == 0) printf("impossible\n");
	}
	return 0;
}

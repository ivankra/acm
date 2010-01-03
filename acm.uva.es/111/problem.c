#include <stdio.h>

#define MAXN 24

int main(void)
{
	static int a[MAXN+8], b[MAXN+8], tmp1;
	static int buf1[MAXN+8], buf2[MAXN+8];
	register int *lcs = buf1, *lcs_next = buf2, n;
	int i;

	scanf("%d", &tmp1); n = tmp1;
	for (i = 1; i <= n; i++) {
		scanf("%d", &tmp1);
		a[tmp1] = i;
	}

	for (;;) {
		for (i = 1; i <= n; i++) {
			if (scanf("%d", &tmp1) < 1) return 0;
			b[tmp1] = i;
		}

		for (i = 0; i <= n; i++)
			lcs[i] = 0;

		for (i = 1; i <= n; i++) {
			register int j, t = a[i];

			for (j = 1; j <= n; j++) {
				if (t == b[j]) {
					lcs_next[j] = 1 + lcs[j - 1];
				} else {
					if (lcs_next[j - 1] > lcs[j])
						lcs_next[j] = lcs_next[j - 1];
					else
						lcs_next[j] = lcs[j];
				}
			}

			if (lcs == buf1) {
				lcs = buf2;
				lcs_next = buf1;
			} else {
				lcs = buf1;
				lcs_next = buf2;
			}
		}

		printf("%d\n", lcs[n]);
	}
}

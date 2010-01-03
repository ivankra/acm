#include <stdio.h>

static int r_leaf, r_sum;

static void tree(int inord[], int postord[], int n, int s)
{
	int i, r;

re:
	if (n <= 0)
		return;

	r = postord[n - 1];
	s += r;

	if (n == 1) {
		if (s < r_sum || (s == r_sum && r < r_leaf)) {
			r_sum = s;
			r_leaf = r;
		}
		return;
	}

	for (i = 0; i < n; i++)
		if (inord[i] == r) break;
	if (i >= n) return;

	if (i == 0) {
		inord += i + 1;
		postord += i;
		n -= i + 1;
		goto re;
	} else if (i == (n - 1)) {
		n = i;
		goto re;
	} else {
		tree(inord + i + 1, postord + i, n - i - 1, s);

		/* tree(inord, postord, i, s); */
		n = i;
		goto re;
	}
}

int main()
{
	static int inord[16384], postord[16384], isdig[256], n, m;
	static char buf[131072];
	register char *p;
	register int i;

	for (i = 0; i < 256; i++)
		isdig[i] = (i >= '0' && i <= '9');

	for (;;) {
		if (fgets(buf, sizeof(buf), stdin) == NULL) break;

		for (n = 0, p = buf;;) {
			while (*p && isdig[(unsigned)*p] == 0) p++;
			if (*p == '\0') break;

			for (i = 0; isdig[(unsigned)*p];)
				i = i * 10 + *p++ - '0';
			inord[n++] = i;
		}

		if (fgets(buf, sizeof(buf), stdin) == NULL) break;

		for (m = 0, p = buf;;) {
			while (*p && isdig[(unsigned)*p] == 0) p++;
			if (*p == '\0') break;

			for (i = 0; isdig[(unsigned)*p];)
				i = i * 10 + *p++ - '0';
			postord[m++] = i;
		}

		if (m < n) n = m;

		r_leaf = 0;
		r_sum = 0x3FFFFFFF;
		tree(inord, postord, n, 0);

		printf("%d\n", r_leaf);
	}

	return 0;
}

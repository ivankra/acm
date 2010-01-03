#include <stdio.h>

static void post(char *pre, char *in, int n)
{
	int k;

	if (n <= 0) return;

	if (n == 1) {
		putchar(pre[0]);
		return;
	}

	for (k = 0; in[k] != pre[0]; k++);

	post(pre + 1, in, k);
	post(pre + k + 1, in + k + 1, n - k - 1);

	putchar(pre[0]);
}

int main()
{
	static char pre[256], in[256];
	static int t, n;

	scanf("%d", &t);

	while (t-- > 0 && scanf("%d %[A-Za-z] %[A-Za-z]", &n, pre, in) == 3) {
		post(pre, in, n);
		putchar('\n');
	}

	return 0;
}

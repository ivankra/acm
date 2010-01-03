/*
ID: mjf28791
PROG: heritage
LANG: C
*/
#include <stdio.h>
#include <string.h>

void post(char *in, char *pre, int n)
{
	int k;

	if (n > 0) {
		for (k = 0; in[k] != pre[0]; k++);

		post(in, pre + 1, k);
		post(in + k + 1, pre + k + 1, n - k - 1);

		putchar(pre[0]);
	}
}

int main()
{
	char in[256], pre[256];

	freopen("heritage.in", "r", stdin);
	scanf("%s %s", in, pre);

	freopen("heritage.out", "w", stdout);
	post(in, pre, strlen(in));
	putchar('\n');

	return 0;
}

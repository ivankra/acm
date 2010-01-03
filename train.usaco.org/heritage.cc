/*
ID: infnty1
PROB: heritage
LANG: C++
*/
#include <cstdio>
#include <cstring>

void go(char *in, char *pre, int n)
{
	int i, r = *pre++;

	if (n < 1) return;
	if (n == 1) { putchar(r); return; }

	for (i = 0; in[i] != r; i++);
	go(in, pre, i);
	go(in+i+1, pre+i, n-1-i);
	putchar(r);
}

int main()
{
	char in[256], pre[256];

	freopen("heritage.in", "r", stdin);
	freopen("heritage.out", "w", stdout);

	scanf(" %s %s", in, pre);
	go(in, pre, strlen(in));
	printf("\n");

	return 0;
}

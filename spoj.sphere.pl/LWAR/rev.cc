#include <stdio.h>
#include <string.h>

char s[65536], r[65536];

void f(int a, int b)
{
again:	if (a > b) return;

	if (a == b) { r[a] = s[a]; return; }

	if (s[a] == '0') {
		for (; a <= b; a++) r[a] = s[a];
		return;
	}

	r[a++] = '1';
	if (s[a] == '0') {
		r[a++] = '1';
		for (; a <= b; a++) r[a] = (s[a] == '0') ? '1' : '0';
		return;
	}
	r[a++] = '0';

	goto again;
}

int main()
{
	int n, t;

	for (scanf("%d", &t); t-- > 0 && scanf(" %s", s) == 1;) {
		n = strlen(s);
		f(0, n-1);
		r[n] = 0;
		printf("%s\n", r);
	}

	return 0;
}

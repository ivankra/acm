#include <stdio.h>
#include <string.h>

char s[65536];

void f(int a, int b)
{
	while (a < b && s[a++] == '1') {
		if (s[a] == '1') {
			for (; a <= b; a++) s[a] = (s[a] == '0') ? '1' : '0';
		} else {
			s[a++] = '1';
		}
	}
}

int main()
{
	int n, t;

	for (scanf("%d", &t); t-- > 0 && scanf(" %s", s) == 1;) {
		f(0, strlen(s)-1);
		printf("%s\n", s);
	}

	return 0;
}

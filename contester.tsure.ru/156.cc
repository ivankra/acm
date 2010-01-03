#include <cstdio>

int main()
{
	char s[256];
	int p = 0, c;
	for (scanf(" %s", s); s[p] && (c = getchar()) != EOF;)
		if ((s[p]|0x20) == (c|0x20)) p++;
	printf(s[p]?"NO\n":"YES\n");
}

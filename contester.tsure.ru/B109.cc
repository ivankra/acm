#include <cstdio>

int main()
{
	char s[1024], c[1024];
	gets(s); gets(c);
	int n=0;
	for (int i = 0; s[i]; i++)
		n += (s[i] == c[0]);
	printf("%d:\n", n);
	n = 0;
	for (int i = 0; s[i]; i++)
		if (s[i] == c[0]) printf(n++?" %d":"%d", i+1);
	printf("\n");
}

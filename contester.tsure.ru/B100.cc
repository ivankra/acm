#include <cstdio>

int main()
{
	int a, b;
	char c;

	scanf(" %d %c %d", &a, &c, &b);
	if (c == '+')
		printf("%d\n", a+b);
	else if (c == '-')
		printf("%d\n", a-b);
	else if (c == '*')
		printf("%d\n", a*b);
	else if (c == '/')
		printf("%d\n", a/b);
}

#include <stdio.h>

int main()
{
	char buf[10000];
	while (gets(buf))
		if (buf[0]) puts(buf);
}

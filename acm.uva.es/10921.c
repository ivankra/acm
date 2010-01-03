#include <stdio.h>

int main()
{
	int map[256], i;

	for (i = 0; i < 256; i++)
		map[i] = i;

	for (i = 0; i < 26; i++)
		map['A'+i] = map['a'+i] = "22233344455566677778889999"[i];

	while ((i = getchar()) != EOF)
		putchar(map[i]);

	return 0;
}

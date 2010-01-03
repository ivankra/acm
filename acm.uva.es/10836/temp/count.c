#include <stdio.h>

int ftab[5][1024], utab[5][1024];

int f(int k, int s)
{
	int i, r;

	if (s < 0 || k < 0)
		return 0;

	if (utab[k][s])
		return ftab[k][s];

	utab[k][s] = 1;

	if (k == 1)
		return (ftab[k][s] = 1);

	for (i = 0, r = 0; i <= s; i++)
		r += f(k - 1, s - i);

	return (ftab[k][s] = r);	
}

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;
	memset(utab, 0, sizeof(utab));
	printf("%d\n", f(4, atoi(argv[1])));
}

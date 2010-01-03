#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i, n;

#ifdef _WIN32
	{ extern int _stdcall GetTickCount(void); srand(GetTickCount()); }
#else
	srand(getpid());
#endif

	n = (argc > 1) ? atoi(argv[1]) : (10 + (rand() % 100000));

	printf("%d\n", n);

	for (i = 0; i < n; i++)
		printf("%d\n", (rand() << 14) ^ rand());

	return 0;
}

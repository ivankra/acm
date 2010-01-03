#include <cstdio>
#include <cstring>
#include <cstdlib>

int main()
{
	int N;
	scanf("%d", &N);

	if (N <= 8) {
		printf("0\n");
	} else if (N == 9) {
		printf("8\n");
	} else {
		printf("72");
		N -= 10;

		char zz[10001];
		memset(zz, '0', sizeof(zz)); zz[10000] = 0;
		for (; N >= 10000; N -= 10000) printf("%s", zz);

		while (N-- > 0) putchar('0');
		printf("\n");
	}

	return 0;
}

#include <stdio.h>

int read(int, unsigned char *, unsigned);

int sol[9][128] = {
	{ 1 },
	{ 1, 1 },
	{ 1, 4, 4 },
	{ 1, 9, 26, 26, 8 },
	{ 1, 16, 92, 232, 260, 112, 16 },
	{ 1, 25, 240, 1124, 2728, 3368, 1960, 440, 32 },
	{ 1, 36, 520, 3896, 16428, 39680, 53744, 38368, 12944, 1600, 64 },
	{ 1, 49, 994, 10894, 70792, 282248, 692320, 1022320, 867328, 389312, 81184, 5792, 128 },
	{ 1, 64, 1736, 26192, 242856, 1444928, 5599888, 14082528, 22522960, 22057472, 12448832, 3672448, 489536, 20224, 256 }
};

int main()
{
	static char inbuf[1048576];
	static int isdig[256];
	register char *inp;
	int i, n, k;

	for (i = '0'; i <= '9'; i++)
		isdig[i] = 1;

	read(0, inp = inbuf, sizeof(inbuf));

#define READ(var) \
	{ while (!isdig[*inp]) inp++; \
	  for (var = *inp++ - '0'; isdig[*inp];) var = var*10 + *inp++ - '0'; }

	for (;;) {
		READ(n);
		if (n == 0) break;

		READ(k);

		printf("%d\n", sol[n][k]);
	}

	return 0;
}

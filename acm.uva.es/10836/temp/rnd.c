#include <stdio.h>

int rnd(unsigned a, unsigned b)
{
	unsigned i, t;

	for (t = 0, i = 0; i < 4; i++)
		t = (t << 8) | (unsigned)((rand() >> 7) & 0xFF);

	t = a + (t % (unsigned)(b - a + 1));

	return (int)t;
}

int main(int argc, char *argv[])
{
	int i, n;

	n = (argc > 1) ? atoi(argv[1]) : 10;
	srand(time(NULL));

	while (n-- > 0) {
		printf("%d %d %d %d %d\n",
			rnd(5, 300),
			rnd(1, 300), rnd(1, 300), rnd(1, 300), rnd(1, 300));
	}

}

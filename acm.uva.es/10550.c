#include <stdio.h>

int main()
{
	int a, b, c, p, r;

	while (scanf("%d %d %d %d", &p, &a, &b, &c) == 4) {
		if ((p | a | b | c) == 0) break;

		for (r = 720; p != a; r += 9)
			if (--p < 0) p = 39;

		for (r += 360; p != b; r += 9)
			if (++p == 40) p = 0;

		for (; p != c; r += 9)
			if (--p < 0) p = 39;

		printf("%d\n", r);
	}

	return 0;
}

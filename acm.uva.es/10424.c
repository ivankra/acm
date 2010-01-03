#include <stdio.h>

static int sum(char *s)
{
	int r, t;

	for (r = 0; *s; s++)
		if (*s >= 'A' && *s <= 'Z')
			r += *s - 'A' + 1;
		else if (*s >= 'a' && *s <= 'z')
			r += *s - 'a' + 1;

	while (r >= 10) {
		for (t = 0; r > 0; r /= 10)
			t += (r % 10);
		r = t;
	}

	return r;
}

int main()
{
	static char a[1024], b[1024];
	static double r;
	static int x, y;

	while (gets(a) && gets(b)) {
		x = sum(a);
		y = sum(b);

		if (x <= y)
			r = 100. * (double)x / (double)y;
		else
			r = 100. * (double)y / (double)x;

		printf("%.2f %%\n", r);
	}

	return 0;
}

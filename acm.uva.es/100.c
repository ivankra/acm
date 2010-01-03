#include <stdio.h>

int cycle(int n)
{
	int len = 1;
	while (n != 1) {
		if ((n % 2) == 0)
			/* n is even */
			n /= 2;
		else
			/* n is odd */
			n = 3 * n + 1;
		len++;
	}

	return len;
}

int main()
{
	int a, b, m, t;

	while (scanf("%d %d", &a, &b) == 2) {

		/* print a and b in the original order */
		printf("%d %d ", a, b);

		if (a > b) {
			/* swap a and b */
			t = a; a = b; b = t;
		}

		/* determine maximum cycle length */
		m = 0;
		for (t = a; t <= b; t++) {
			int c = cycle(t);
			if (c > m) m = c;
		}

		printf("%d\n", m);
	}

	return 0;
}

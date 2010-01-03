#include <stdio.h>
#include <string.h>

int main()
{
	static int r[1024];
	int k, p, q;

	while (scanf("%d %d", &p, &q) == 2 && q > 0) {
		memset(r, 0, sizeof(r));

		putchar('.');
		for (k = 1; p != 0 && r[p] == 0; k++) {
			if ((k % 50) == 0)
				putchar('\n');
			r[p] = k;
			putchar(((p * 10) / q) + '0');
			p = (p * 10) % q;
		}

		if (p == 0)
			printf("\nThis expansion terminates.\n\n");
		else
			printf("\nThe last %d digits repeat forever.\n\n",
				k - r[p]);
	}

	return 0;
}

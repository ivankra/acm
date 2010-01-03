#include <stdio.h>

int main()
{
	static int f[256], v[256];
	int i, j, k, c;

	for (;;) {
		for (i = 0; i < 256; i++)
			f[i] = 0;

		for (i = 0; (c = getchar()) != EOF && c != '\n';)
			if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
				f[c]++, i++;

		if (i == 0)
			break;

		for (i = 0, c = 0; i < 256; i++)
			if (f[i] > c) c = f[i];

		for (i = 0, k = 0; i < 256; i++)
			if (f[i] == c) v[k++] = i;

		for (i = 1; i < k; i++) {
			for (c = v[i], j = i - 1; j >= 0 && v[j] > c; j--)
				v[j + 1] = v[j];
			v[j + 1] = c;
		}

		for (i = 0; i < k; i++)
			putchar(v[i]);

		printf(" %d\n", f[v[0]]);
	}

	return 0;
}

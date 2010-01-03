#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
	static int a[256], b[256];
	static char s[1024];
	int i, j, n, r, t;

	while (gets(s) && sscanf(s, "%d", &t) != 1);

	while (t-- > 0 && gets(s)) {
		for (i = n = 0; sscanf(s + i, "%d%n", &a[n], &r) >= 1; i += r, n++);

		for (r = 0, i = 0; i < n; i++)
			r += a[i];
		assert(r <= 255);

		if ((r % 2) != 0) {
			printf("NO\n");
			continue;
		}
		r /= 2;

		memset(b, 0, sizeof(b));
		b[0] = 1;

		for (i = 0; i < n; i++)
			for (j = r; j >= 0; j--)
				if (b[j]) b[j + a[i]] = 1;

		printf(b[r] ? "YES\n" : "NO\n");
	}

	return 0;
}

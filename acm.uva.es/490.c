#include <stdio.h>
#include <string.h>

int main()
{
	static char s[128][128], buf[256];
	int i, j, k, m, n;

	memset(s, '\0', sizeof(s));
	for (n = 0; gets(s[n]); n++);

	for (i = 0, m = 0; i < n; i++) {
		for (j = 0; s[i][j]; j++);
		if (j > m) m = j;
	}

	for (i = 0; i < m; i++) {
		for (j = n - 1, k = 0; j >= 0; j--)
			buf[k++] = s[j][i];

		while (k > 0 && buf[k - 1] == '\0') k--;
		buf[k] = '\0';

		for (j = 0; j < k; j++)
			if (buf[j] == '\0') buf[j] = ' ';

		printf("%s\n", buf);
	}

	return 0;
}

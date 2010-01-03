#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
	char buf[4096];
	int f[256], s[256], i, j;

	int first = 1;
	while (fgets(buf, sizeof(buf), stdin)) {
		assert(strlen(buf) > 0);

		if (first == 0) printf("\n");
		first = 0;

		for (i = 0; i < 256; i++)
			f[i] = 0;

		for (i = 0; buf[i] && buf[i] != '\r' && buf[i] != '\n'; i++)
			f[(int)buf[i]]++;

		for (s[0] = 0, i = 1; i < 256; i++) {
			for (j = i - 1; j >= 0 && f[s[j]] >= f[i]; j--)
				s[j + 1] = s[j];
			s[j + 1] = i;
		}

		for (i = 0; i < 256; i++)
			if (f[s[i]])
				printf("%d %d\n", s[i], f[s[i]]);
	}

	return 0;
}

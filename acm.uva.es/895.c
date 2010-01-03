#include <stdio.h>

int main()
{
	static int dict[1024][32], count[32];
	static char buf[1024];
	int i, j, k, n;

	for (n = 0; gets(buf) && buf[0] != '#';) {
		for (i = 0; i < 26; i++) dict[n][i] = 0;
		for (i = 0; buf[i]; i++)
			if (buf[i] >= 'a' && buf[i] <= 'z')
				dict[n][buf[i] - 'a']++;
		n++;
	}

	while (gets(buf) && buf[0] != '#') {
		for (i = 0; i < 26; i++) count[i] = 0;
		for (i = 0; buf[i]; i++)
			if (buf[i] >= 'a' && buf[i] <= 'z')
				count[buf[i] - 'a']++;

		for (i = 0, k = 0; i < n; i++) {
			for (j = 0; j < 26; j++)
				if (dict[i][j] > count[j]) break;
			if (j >= 26) k++;
		}

		printf("%d\n", k);
	}

	return 0;
}

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char buf[65536];
int freq[128];

int main()
{
	char *p;
	int i;

	memset(freq, 0, sizeof(freq));
	i = 0;

	while (gets(buf)) {
		if (buf[0] == '#') {
			for (i = 1; i < 80; i++)
				if (freq[i] != 0) printf("%d %d\n", i, freq[i]);
			printf("\n");

			memset(freq, 0, sizeof(freq));
			i = 0;

			continue;
		}

		if (buf[0] == '\0')
			continue;

		for (p = buf; *p; p++) {
			if (isalpha(*p)) {
				i++;
			} else if (*p != '\'' && *p != '-') {
				freq[i]++;
				i = 0;
			}
		}

		if (p[-1] != '-') {
			freq[i]++;
			i = 0;
		}
	}

	return 0;
}

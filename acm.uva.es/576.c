#include <stdio.h>
#include <string.h>

int main()
{
	static char line[65536];
	static int syl[16], isvowel[256];
	char *p;
	int i;

	memset(isvowel, 0, sizeof(isvowel));
	for (p = "aeiouyAEIOUY"; *p;)
		isvowel[(unsigned)*p++] = 1;

	while (gets(line)) {
		if (strcmp(line, "e/o/i") == 0)
			break;

		memset(syl, 0, sizeof(syl));
		for (p = line, i = 0; i < 3 && *p;) {
			while (*p && *p != '/' && !isvowel[(unsigned)*p])
				p++;

			if (*p == '/') {
				p++, i++;
			} else if (isvowel[(unsigned)*p]) {
				syl[i]++;
				while (isvowel[(unsigned)*p])
					p++;
			} else if (*p != '\0') {
				p++;
			}
		}

		if (syl[0] != 5)
			printf("1\n");
		else if (syl[1] != 7)
			printf("2\n");
		else if (syl[2] != 5)
			printf("3\n");
		else
			printf("Y\n");
	}

	return 0;
}

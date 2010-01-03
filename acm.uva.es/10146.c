#include <stdio.h>
#include <string.h>

int main()
{
	static char buf[4096], s[4096];
	int i, m, t;

	while (gets(buf) && sscanf(buf, "%d", &t) != 1);
	gets(buf);

	for (m = 0; t > 0 && gets(buf);) {
		if (buf[0] == '\0') {
			if (--t <= 0)
				break;

			printf("\n");
			m = 0;
			continue;
		}

		for (i = 0; i < m && buf[i] == s[i]; i++)
			putchar(' ');

		m = i + 1;
		if (m > strlen(buf))
			m = strlen(buf);

		for (i = 0; i < m; i++)
			s[i] = buf[i];

		printf("%s\n", buf);
	}

	return 0;
}

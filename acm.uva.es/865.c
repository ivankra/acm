#include <stdio.h>
#include <memory.h>

char buf[256], buf2[256], tab[256];
int i, t;

int main()
{
	scanf("%d\n\n", &t);

	while (t-- > 0) {
		memset(buf, 0, sizeof(buf));
		gets(buf);

		memset(buf2, 0, sizeof(buf2));
		gets(buf2);

		for (i = 0; i < 256; i++)
			tab[i] = i;

		for (i = 0; buf[i]; i++)
			tab[(unsigned)buf[i]] = buf2[i];

		printf("%s\n", buf2);
		printf("%s\n", buf);

		memset(buf, '\0', sizeof(buf));
		while (gets(buf) && buf[0] != '\0') {
			for (i = 0; buf[i]; i++)
				buf[i] = tab[(unsigned)buf[i]];
			printf("%s\n", buf);
			memset(buf, '\0', sizeof(buf));
		}

		if (t > 0) printf("\n");
	}

	return 0;
}

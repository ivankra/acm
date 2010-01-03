#include <stdio.h>
#include <string.h>

char buf[24*1048576];
int to[256];

int main()
{
	int i, j;

	memset(to, 0, sizeof(to));
	for (i = 0; i < 26; i++) to[i+'a'] = to[i+'A'] = 'a'+i;

	while (gets(buf) && strcmp(buf, "DONE") != 0) {
		for (i = 0, j = 0; buf[i]; i++)
			if (to[buf[i]] != 0) buf[j++] = to[buf[i]];

		for (i = 0; j-- > 0; i++)
			if (buf[j] != buf[i]) goto NO;
		printf("You won't be eaten!\n");
		continue;

NO:		printf("Uh oh..\n"); continue;
	}

	return 0;
}

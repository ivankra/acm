#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[256][256], result[256], s1[256], s2[256];
int inlen[256], marked[256], count, width, maxlen;

int mark(char *s, char *t)
{
	int i, j;

	for (i = 0; i < count; i++)
		if (!marked[i] && strcmp(input[i], s) == 0) break;

	if (i >= count)
		return 0;

	for (j = 0; j < count; j++)
		if (!marked[j] && strcmp(input[j], t) == 0) break;

	if (j >= count)
		return 0;

	marked[i] = 1;
	marked[j] = 1;
	return 1;
}

int check()
{
	char s[1024], t[1024];
	int i;

	for (i = 0; i < count; i++)
		marked[i] = 0;

	for (i = 0; i < count; i++) {
		if (marked[i])
			continue;

		strcpy(s, result);
		s[inlen[i]] = 0;
		strcpy(t, result + inlen[i]);

		if (mark(s, t))
			continue;

		strcpy(s, result);
		s[width - inlen[i]] = 0;

		if (mark(s, result + width - inlen[i]))
			continue;

		return 0;
	}

	return 1;
}

int main()
{
	char buf[1024];
	int i, j, t;

	for (scanf("%d", &t); t-- > 0;) {
		for (count = 0; gets(buf);) {
			if (sscanf(buf, " %[0-9]", input[count]) == 1)
				count++;
			else if (count != 0)
				break;
		}

		for (i = 0; i < count; i++)
			inlen[i] = strlen(input[i]);

		for (j = inlen[0], i = 1; i < count; i++)
			if (inlen[i] > j) j = inlen[i];
		maxlen = j;

		for (j = inlen[0], i = 1; i < count; i++)
			if (inlen[i] < j) j = inlen[i];
		width = maxlen + j;

		for (i = 0; i < count; i++)
			if (inlen[i] == maxlen) break;
		strcpy(s1, input[i]);

		for (i = 0; i < count; i++) {
			if (inlen[i] == (width - maxlen) &&
			    memcmp(input[i], s1, width - maxlen) != 0) break;
		}

		if (i >= count) {
			for (i = 0; i < count; i++)
				if (inlen[i] == (width - maxlen)) break;
		}
		strcpy(s2, input[i]);

		sprintf(result, "%s%s", s1, s2);

		if (check())
			printf("%s%s\n", s1, s2);
		else
			printf("%s%s\n", s2, s1);

		if (t > 0) printf("\n");
	}

	return 0;
}

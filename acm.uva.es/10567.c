#include <stdio.h>
#include <string.h>

char buffer[2097152], *query[4096], *ptr[4096];
int next[4096], head[256], first[256], last[4096], m;

int main()
{
	char *s;
	int i, j;

	gets(buffer);
	s = buffer + strlen(buffer) + 1;

	while (gets(s) && sscanf(s, "%d", &m) != 1);

	for (i = 1; i <= m; i++) {
		gets(query[i] = ptr[i] = s);
		while (*s++);
	}

	memset(next, 0, sizeof(next));
	memset(head, 0, sizeof(head));

	for (i = 0; i < 256; i++)
		first[i] = -1;

	for (i = 1; i <= m; i++) {
		last[i] = -1;
		if (ptr[i][0] != '\0') {
			next[i] = head[ptr[i][0]];
			head[ptr[i][0]] = i;
		}
	}

	for (s = buffer; *s; s++) {
		i = head[*s];
		if (i == 0) continue;

		if (first[*s] < 0)
			first[*s] = s - buffer;

		next[j = 0] = head[*s];
		while (i != 0) {
			ptr[i]++;
			if (ptr[i][0] == '\0') {
				last[i] = s - buffer;
				next[j] = i = next[i];
			} else if (ptr[i][0] == *s) {
				j = i;
				i = next[i];
			} else {
				next[j] = next[i];
				next[i] = head[ptr[i][0]];
				head[ptr[i][0]] = i;
				i = next[j];
			}
		}
		head[*s] = next[0];
	}

	for (i = 1; i <= m; i++)
		if (last[i] < 0)
			printf("Not matched\n");
		else
			printf("Matched %d %d\n", first[query[i][0]], last[i]);

	return 0;
}


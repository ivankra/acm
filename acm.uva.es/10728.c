#include <stdio.h>
#include <string.h>
#include <ctype.h>

int uf[1024], count[1024], repl[1024], ndict;
char dict[1024][128];

int get(char *s)
{
	int i;
	for (i = 0; i < ndict; i++)
		if (strcmp(dict[i], s) == 0) return i;
	strcpy(dict[ndict], s);
	return ndict++;
}

int parse(int r[], char *s, int id)
{
	static char w[1024];
	int i, m;

	for (m = i = 0;; s++) {
		if (*s && (isalpha(*s) || *s == '<')) {
			w[i++] = *s;
		} else if (i > 0) {
			if (w[0] == '<') w[i++] = id;
			w[i] = 0;
			r[m++] = get(w);
			i = 0;
		}
		if (*s == '\0') break;
	}

	return m;
}

int find(int x)
{
	int z;
	for (z = x; uf[z] != z; z = uf[z]);
	return (uf[x] = z);
}

int main()
{
	static int a[1024], b[1024], len, t;
	static char s[1024];
	int i, j;

	while (gets(s) && sscanf(s, "%d", &t) != 1);

	while (t-- > 0) {
		ndict = 0;

		gets(s);
		len = parse(a, s, '1');

		gets(s);
		if (parse(b, s, '2') != len) goto fail;

		for (i = 0; i < ndict; i++)
			uf[i] = i;

		for (i = 0; i < len; i++)
			uf[find(a[i])] = find(b[i]);

		memset(count, 0, sizeof(count));

		for (i = 0; i < ndict; i++)
			if (dict[i][0] != '<') {
				count[find(i)]++;
				repl[find(i)] = i;
			}

		for (i = 0; i < ndict; i++)
			if (count[i] > 1) goto fail;

		for (i = 0; i < len; i++) {
			j = find(a[i]);
			if (count[j] < 1)
				printf("a");
			else
				printf("%s", dict[repl[j]]);
			if ((i + 1) < len) printf(" ");
		}
		printf("\n");

		continue;

fail:		printf("-\n");
	}

	return 0;
}

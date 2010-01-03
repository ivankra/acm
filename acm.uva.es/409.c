#include <stdio.h>
#include <string.h>
#include <ctype.h>

static char buf[4096], text[32][4096], kw[32][256];
static int cnt[256], k, n, t;

static int count(char *s)
{
	static char w[1024];
	int i, r;

	for (r = 0;;) {
		while (*s && !isalpha(*s)) s++;

		if (*s == '\0')
			break;

		for (i = 0; *s && isalpha(*s);)
			w[i++] = tolower(*s++);
		w[i] = '\0';

		for (i = 0; i < k; i++)
			if (strcmp(w, kw[i]) == 0) break;

		if (i < k) r++;
	}

	return r;
}

int main()
{
	int i, j;

	for (t = 1; gets(buf);) {
		if (sscanf(buf, "%d %d", &k, &n) != 2) continue;

		for (i = 0; i < k; i++) {
			gets(kw[i]);
			for (j = 0; kw[i][j]; j++)
				kw[i][j] = tolower(kw[i][j]);
		}

		for (i = j = 0; i < n; i++) {
			gets(text[i]);
			cnt[i] = count(text[i]);
			if (i == 0 || cnt[i] > j) j = cnt[i];
		}

		printf("Excuse Set #%d\n", t++);
		for (i = 0; i < n; i++)
			if (cnt[i] == j) printf("%s\n", text[i]);
		printf("\n");
	}

	return 0;
}

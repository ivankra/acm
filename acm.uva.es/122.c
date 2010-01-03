#include <stdio.h>
#include <string.h>
#include <ctype.h>

int left[65536], right[65536], use[65536], value[65536], last;

void search()
{
	static int s[65536];
	int i, h, t;

	s[0] = 1;
	h = 0;
	t = 1;

	while (h < t) {
		printf(h ? " %d" : "%d", value[s[h]]);
		i = s[h++];
		if (left[i] != 0) s[t++] = left[i];
		if (right[i] != 0) s[t++] = right[i];
	}

	printf("\n");
}

void add(int v, char *s)
{
	int r;

	for (r = 1; *s; s++) {
		if (*s == 'L') {
			if (left[r] == 0) {
				left[r] = ++last;
				r = left[r];
				left[r] = right[r] = use[r] = 0;
			} else {
				r = left[r];
			}
		} else {
			if (right[r] == 0) {
				right[r] = ++last;
				r = right[r];
				left[r] = right[r] = use[r] = 0;
			} else {
				r = right[r];
			}
		}
	}

	use[r]++;
	value[r] = v;
}

int main()
{
	static char s[1024];
	int i, j, c, n, v;

	for (;;) {
		left[1] = right[1] = use[1] = 0;
		last = 1;

		for (n = 0;; n++) {
			while ((c = getchar()) != EOF && c != '(');
			if (c != '(') break;

			for (i = 0; (c = getchar()) != EOF && c != ')';)
				s[i++] = toupper(c);
			s[i] = '\0';

			if (s[0] == '\0')
				break;

			sscanf(s, "%d", &v);

			for (i = 0; s[i] && s[i] != ','; i++);
			if (s[i] == ',') i++;

			for (j = 0; s[i]; i++)
				if (s[i] == 'L' || s[i] == 'R') s[j++] = s[i];
			s[j] = '\0';

			add(v, s);
		}

		if (n == 0)
			break;

		for (i = 1; i <= last; i++)
			if (use[i] != 1) break;

		if (i <= last) {
			printf("not complete\n");
			continue;
		}

		search();
	}

	return 0;
}

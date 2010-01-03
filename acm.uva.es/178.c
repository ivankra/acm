#include <stdio.h>
#include <string.h>
#include <ctype.h>

int top[64], count[64], n;

int get()
{
	static char s[] = "A23456789TJQK";
	int c, t;

	while ((c = getchar()) != EOF && c != '#' && !isalnum(c));

	if (c == '#') ungetc(c, stdin);
	if (c == EOF || c == '#') return -1;

	while ((t = getchar()) != EOF && !isalnum(t));

	return (strchr(s, toupper(c)) - s) + 1;
}

void find2(int x[])
{
	int i, j;

	for (i = 0; i < n; i++) {
		if (top[i] > 10) continue;

		for (j = i + 1; j < n; j++) {
			if (top[j] > 10 || (top[i] + top[j]) != 11) continue;

			x[0] = i;
			x[1] = j;
			return;
		}
	}
}

void find3(int x[])
{
	int i, j, k;

	for (i = 0; i < n; i++) {
		if (top[i] <= 10) continue;

		for (j = i + 1; j < n; j++) {
			if (top[j] <= 10 || top[j] == top[i]) continue;

			for (k = j + 1; k < n; k++) {
				if (top[k] <= 10 || top[k] == top[i] ||
				    top[k] == top[j])
					continue;

				x[0] = i;
				x[1] = j;
				x[2] = k;
				return;
			}
		}
	}
}

int main()
{
	int a[64], x[4], y[4], i, t;

	for (t = 1;; t++) {
		for (i = 0; i < 52 && (a[i] = get()) > 0; i++);
		if (i < 52) break;

		n = 0;

		for (i = 0; i < 52;) {
			x[0] = y[0] = 100;
			find2(x);
			find3(y);

			if (x[0] == 100 && y[0] == 100) {
				if (n == 16) break;
				top[n] = a[i++];
				count[n++] = 1;
			} else if (x[0] < y[0]) {
				if (i < 52) top[x[0]] = a[i++], count[x[0]]++;
				if (i < 52) top[x[1]] = a[i++], count[x[1]]++;
			} else {
				if (i < 52) top[y[0]] = a[i++], count[y[0]]++;
				if (i < 52) top[y[1]] = a[i++], count[y[1]]++;
				if (i < 52) top[y[2]] = a[i++], count[y[2]]++;
			}
		}

		if (i < 52) {
			printf("%3d: Overflowed on card no %d\n", t, i + 1);
			continue;
		}

		printf("%3d:", t);
		for (i = 0; i < n; i++)
			printf("%3d", count[i]);
		printf("\n");
	}

	return 0;
}

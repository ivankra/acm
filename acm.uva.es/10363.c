#include <stdio.h>

int a[16], r[32768];

int get()
{
	int i, m;

	for (m = 0, i = 0; i < 9; i++)
		m = m * 3 + a[i];

	return m;
}

int win()
{
	int i;

	for (i = 0; i < 9; i += 3)
		if (a[i] != 0 && a[i] == a[i + 1] && a[i] == a[i + 2]) return 1;

	for (i = 0; i < 3; i++)
		if (a[i] != 0 && a[i] == a[i + 3] && a[i] == a[i + 6]) return 1;

	if (a[4] == 0)
		return 0;

	return ((a[4] == a[0] && a[4] == a[8]) ||
		(a[4] == a[2] && a[4] == a[6]));
}

void go(int p)
{
	int i;

	for (i = 0; i < 9; i++) {
		if (a[i] == 0) {
			a[i] = p;
			if (r[get()]++ == 0 && !win())
				go(3 - p);
			a[i] = 0;
		}
	}
}

int main()
{
	int i, c, k, t;

	memset(r, 0, sizeof(r));

	memset(a, 0, sizeof(a));
	r[get()] = 1;

	go(1);

	for (scanf("%d", &t); t-- > 0;) {
		for (k = 0, i = 0; i < 9 && (c = getchar()) != EOF;) {
			if (c == '.') {
				k *= 3;
				i++;
			} else if (c == 'X') {
				k = k * 3 + 1;
				i++;
			} else if (c == 'O') {
				k = k * 3 + 2;
				i++;
			}
		}

		printf(r[k] ? "yes\n" : "no\n");
	}

	return 0;
}

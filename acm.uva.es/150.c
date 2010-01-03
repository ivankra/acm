#include <stdio.h>

int day(int y, int m, int d, int x)
{
	static int s[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
	int r;

	y--;
	r = y * 365 + y / 4 + s[m - 1] + d - 1;
	if (x) r = r - y / 100 + y / 400;

	y++;
	if (m >= 3 && (y % 4) == 0 && (!x || (y % 100) != 0 || (y % 400) == 0))
		r++;

	if (x) r += 2;

	return r;
}

int weekday(int y, int m, int d, int x)
{
	return (day(y, m, d, x) + 6) % 7;
}

void next(int *y, int *m, int *d, int x)
{
	static int s[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	(*d)++;
	if ((*d) > s[*m]) {
		if ((*m) == 2 && (*d) == 29 && ((*y) % 4) == 0 &&
		    (!x || ((*y) % 100) != 0 || ((*y) % 400) == 0))
			return;
		(*d) = 1;
		(*m)++;
	}

	if ((*m) > 12) {
		(*m) = 1;
		(*y)++;
	}
}

int get(char *s, char *q)
{
	int i;

	for (i = 0; i < 3; i++)
		s[i] |= 0x20;

	for (i = 0; *q; i++, q += 3)
		if (s[0] == q[0] && s[1] == q[1] && s[2] == q[2]) break;

	return i;
}

int main()
{
	char *sw[] = {
		"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
		"Friday", "Saturday"
	};
	char *sm[] = {
		"", "January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November",
		"December"
	};
	char s1[1024], s2[1024];
	int d, y, m, w, t;

	while (scanf("%s %d %s %d", s1, &d, s2, &y) == 4 && s1[0] != '#') {
		w = get(s1, "sunmontuewedthufrisat");
		m = 1 + get(s2, "janfebmaraprmayjunjulaugsepoctnovdec");

		if (weekday(y, m, d, 0) == w) {
			t = day(y, m, d, 0);

			while (day(y, m, d, 1) != t)
				next(&y, &m, &d, 1);

			printf("%s %d %s %d\n",
				sw[weekday(y, m, d, 1)], d, sm[m], y);
		} else {
			t = day(y, m, d, 1);

			d = 1;
			m--;
			if (m < 1) y--, m = 12;

			while (day(y, m, d, 0) != t)
				next(&y, &m, &d, 0);

			printf("%s %d* %s %d\n",
				sw[weekday(y, m, d, 0)], d, sm[m], y);
		}
	}

	return 0;
}

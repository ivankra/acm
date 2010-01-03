#include <stdio.h>

/* Returns number of days since Jan 1, 1601.
   Does not include 1752's correction. */
static int to_days(int m, int d, int y)
{
	static int l[12] = { 0,31,59,90,120,151,181,212,243,273,304,334 };
	int t;

	t = (y - 1601) * 365;
	t += (y - 1601) / 4;
	t -= (y - 1601) / 100;
	t += (y - 1601) / 400;

	t += l[m - 1] + d - 1;

	if (m >= 3 && (y & 3) == 0 && ((y % 100) != 0 || (y % 400) == 0))
		t++;

	return t;
}

static void from_days(int *m, int *d, int *y, int t)
{
	static int l[12] = { 31,29, 31,30,31, 30,31,31, 30,31,30, 31 };
	int i;

	(*y) = 1601 + 400 * (t / 146097);
	t %= 146097;

	i = t / 36524;
	if (i > 3) i = 3;
	t = (t + i) % 36525;
	if (i < 3 && t >= 36218)
		t++;
	(*y) += i * 100;

	(*y) += (t / 1461) << 2;
	t %= 1461;

	i = t / 365;
	if (i > 3) i = 3;
	t = (t + i) % 366;
	if (i < 3 && t >= 59)
		t++;
	(*y) += i;

	for (i = 0; i < 11 && t >= l[i]; i++)
		t -= l[i];
	(*m) = i + 1;
	(*d) = t + 1;
}

int main(void)
{
	int m, d, y, n;

	while (scanf("%d %d %d %d", &n, &d, &m, &y) == 4 && (m && d && y)) {
		from_days(&m, &d, &y, n + to_days(m, d, y));
		printf("%d %d %d\n", d, m, y);
	}

	return 0;
}

#include <stdio.h>
#include <stdlib.h>

static int cvt(int m, int d, int y)
{
	static int s[12] = { 0,31,59,90,120,151,181,212,243,273,304,334 };
	static int l[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	register int t;

	if (y <= 0 || m <= 0 || m > 12 || d <= 0 || d > l[m - 1]) return -1;
	if (y == 1752 && m == 9 && (d > 2 && d < 14)) return -2;

	t = ((y - 1) * 365) + ((y - 1) >> 2);
	if (y > 1752 || (y == 1752 && (m > 9 || (m == 9 && d > 2)))) {
		t = t - ((y - 1) / 100) + ((y - 1) / 400) + 2;
		if ((y & 3) == 0 && ((y % 100) != 0 || (y % 400) == 0)) {
			if (m > 2) t++;
		} else if (m == 2 && d > 28) {
			return -3;
		}
	} else {
		if ((y & 3) == 0) {
			if (m > 2) t++;
		} else if (m == 2 && d > 28) {
			return -4;
		}
	}

	return t + s[m - 1] + d - 1;
}

int main(int argc, char *argv[])
{
	static const char *wd[] = {
		"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
		"Friday", "Saturday"
	};
	static const char *mn[] = {
		"January", "February",
		"March", "April", "May",
		"June", "July", "August",
		"September", "October", "November",
		"December"
	};
	int m, d, y, t, w;

	while (scanf("%d %d %d", &m, &d, &y) == 3 && (m || d || y)) {
		t = cvt(m, d, y);
		if (t < 0) {
			printf("%d/%d/%d is an invalid date.\n", m, d, y);
		} else {
			w = (6 + t) % 7;
			printf("%s %d, %d is a %s\n",
				mn[m - 1], d, y, wd[(6 + t) % 7]);
		}
	}

	return 0;
}

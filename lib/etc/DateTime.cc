#include <cstdio>

char *weekdayName[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
        "Friday", "Saturday"
};

char *monthName[] = {
        "January", "February", "March", "April", "May", "June", "July",
        "August", "September", "October", "November", "December"
};      

/* x = new style(1) / old style(0) */
int weekday(int y, int m, int d, int x = 1) {
	int s[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

	y--;
	int r = y * 365 + y / 4 + s[m-1] + d - 1;
	if (x) r = r - y / 100 + y / 400;

	y++;
	if (m >= 3 && (y % 4) == 0 && (!x || (y % 100) != 0 || (y % 400) == 0))
		r++;

	return (r + 6 + 2*x) % 7;
}

int main()
{
	int d, y, m;
	while (scanf("%d %d %d", &y, &m, &d) == 3)
		printf("%s\n", weekdayName[weekday(y, m, d, 1)]);
}

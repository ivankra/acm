#include <cstdio>
#include <cstring>
#include <cassert>

struct Date {
	int y, m, d, w;

	static int IsLeap(int y) {
		return (y%4)==0 && ((y%100)!=0 || (y%400)==0);
	}

	static int DaysInMonth(int y, int m) {
		if (m == 2) return IsLeap(y) ? 29 : 28;
		static int r[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
		return r[m];
	}

	void operator ++() {
		if (++d > DaysInMonth(y, m)) {
			d = 1;
			if (++m > 12) {
				m = 1;
				y++;
			}
		}
		w = (w + 1) % 7;
	}

	void operator --() {
		if (--d < 1) {
			if (--m < 1) {
				m = 12;
				y--;
			}
			d = DaysInMonth(y, m);
		}
		w = (w + 6) % 7;
	}

	bool operator <(const Date &b) const {
		if (y != b.y) return y < b.y;
		if (m != b.m) return m < b.m;
		return d < b.d;
	}
};

int main()
{
	Date now; scanf("%d %d %d", &now.d, &now.m, &now.y);

	Date d={2006,5,7,6};
	while (d < now) ++d;
	while (now < d || d.d > 1) --d;

	char out[8][64];
	memset(out, ' ', sizeof(out));

	for (int i = 0; i < 7; i++)
		memcpy(out[i], "montuewedthufrisatsun"+i*3, 3);

	int row = d.w, col = 0;
	for (int day = 1; day <= Date::DaysInMonth(d.y, d.m); day++) {
		char s[16];
		sprintf(s, "%c%2d%c", day==now.d?'[':' ', day, day==now.d?']':' ');
		memcpy(out[row]+4+5*col, s, strlen(s));
		if (++row > 6) { row = 0; col++; }
	}

	for (int i = 0, j = 0; i < 7; i++) {
		out[i][60] = 0;
		for (j = 0; out[i][j]; j++)
			if (out[i][j] == ' ') out[i][j] = '.';
		while (j > 0 && out[i][j-1] == '.')
			out[i][--j] = 0;
		printf("%s\n", out[i]);
	}
}

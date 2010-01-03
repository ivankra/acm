#include <stdio.h>

int lastoff, lastneg, lastaw, lastred, lastpt, day, pt;

void print(int d, int p)
{
	printf("%.4d-%.2d-%.2d ", d / 10000, (d / 100) % 100, d % 100);
	if (p == 0)
		printf("No merit or demerit points.\n");
	else if (p > 0)
		printf("%d merit point(s).\n", p);
	else
		printf("%d demerit point(s).\n", -p);
}

void upd()
{
	if (lastpt != pt) {
		print(day, pt);
		lastpt = pt;
	}
}

void next()
{
	int t;

	if (pt >= 0) {
		if ((day - lastneg) >= 20000 && (day - lastaw) >= 20000) {
			pt++;
			lastaw = day;
		}
	} else if ((day - lastoff) >= 10000 && (day - lastred) >= 10000) {
		t = (-pt + 1) / 2;
		if (t < 2) t = 2;
		lastred = day;

		pt += t;
		if (pt >= 0) {
			pt = 0;
			lastaw = day;
		}
	}

	if (pt < 0) lastneg = day;

	upd();
}

int main()
{
	static char s[1024];
	int t, x, y;

	for (scanf("%d", &t); t-- > 0;) {
		for (pt = 0; gets(s) && sscanf(s, "%d", &day) != 1;);
		lastneg = lastoff = lastpt = -0x1fffffff;
		lastaw = lastred = day;

		upd();

		while (gets(s) && sscanf(s, "%d %d", &x, &y) == 2) {
			upd();

			while ((day + 10000) <= x) {
				next();
				day += 10000;
			}

			if (day <= x)
				next();

			if (pt >= 0) {
				if (y > (2 * pt)) {
					y -= 2 * pt;
					pt = -y;
				} else {
					y = 0;
					pt -= (y + 1) / 2;
				}
			} else {
				pt -= y;
				lastred = x;
			}

			lastoff = x;
			lastneg = x;
			day = x;

			upd();
		}

		while (pt < 5) {
			next();
			day += 10000;
		}

		if (t) printf("\n");
	}

	return 0;
}

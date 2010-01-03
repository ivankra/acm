#include <stdio.h>

char *digit_s[] = {
	"YYYYYYN", "NYYNNNN", "YYNYYNY", "YYYYNNY", "NYYNNYY", "YNYYNYY",
	"YNYYYYY", "YYYNNNN", "YYYYYYY", "YYYYNYY"
};

int digit[10], seq[16], n;

int check(int s)
{
	int i, d, m;

	if ((s - n + 1) < 0)
		return 0;

	for (m = 0, i = 0; i < n; i++) {
		d = s - i;

		if (seq[i] & m)
			return 0;

		if ((seq[i] & ~digit[d]) != 0)
			return 0;

		m |= digit[d] & ~seq[i];
	}

	return 1;
}

int solve()
{
	int s;

	for (s = 9; s >= 0; s--)
		if (check(s)) return 1;

	return 0;
}

int cvt(char *s)
{
	int a;

	for (a = 0; *s; s++)
		if (*s == 'Y')
			a = (a << 1) | 1;
		else
			a <<= 1;

	return a;
}

int main()
{
	static char s[1024];
	int i;

	for (i = 0; i <= 9; i++)
		digit[i] = cvt(digit_s[i]);

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n && scanf(" %s", s) == 1; i++)
			seq[i] = cvt(s);

		printf(solve() ? "MATCH\n" : "MISMATCH\n");
	}

	return 0;
}

/*
ID: mjf28791
PROG: clock
LANG: C
*/
#include <stdio.h>
#include <string.h>

char *spell(char *buf, int x, int cap)
{
	char *small[] = {
		"zero", "one", "two", "three", "four", "five", "six",
		"seven", "eight", "nine", "ten", "eleven", "twelve",
		"thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
		"eighteen", "nineteen"
	}, *dec[] = {
		"zero", "ten", "twenty", "thirty", "forty", "fifty", "sixty"
	};

	if (x < 20)
		strcpy(buf, small[x]);
	else
		sprintf(buf, (x % 10) ? "%s-%s" : "%s",
			dec[x / 10], small[x % 10]);

	if (cap)
		buf[0] = buf[0] - 'a' + 'A';

	return buf;		
}

int nexthr(int h)
{
	return 1 + (h % 12);
}

int main()
{
	int h, m;
	char s[256], t[256];

	freopen("clock.in", "r", stdin);
	freopen("clock.out", "w", stdout);

	scanf(" %d : %d", &h, &m);

	if (m == 0)
		printf("%s o'clock\n", spell(s, h, 1));
	else if (m == 15)
		printf("Quarter past %s\n", spell(s, h, 0));
	else if (m == 30)
		printf("%s thirty\n", spell(s, h, 1));
	else if (m == 45)
		printf("Quarter to %s\n", spell(s, nexthr(h), 0));
	else if (m < 45)
		printf("%s %s\n", spell(s, h, 1), spell(t, m, 0));
	else
		printf("%s to %s\n",
			spell(s, 60 - m, 1), spell(t, nexthr(h), 0));

	return 0;
}

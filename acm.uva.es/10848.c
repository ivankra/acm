#include <stdio.h>
#include <string.h>
#include <ctype.h>

char buf[65536], s1[65536], s2[65536];
int count1[32], count2[32], cost_10453;

int check7()
{
	return (cost_10453 < strlen(s1));
}

int check6()
{
	return (strlen(s2) == (strlen(s1) + cost_10453));
}

int check5()
{
	char *p, *q;

	for (p = s1, q = s2; *p && *q;) {
		if (*p == *q) {
			p++;
			q++;
		} else {
			q++;
		}
	}

	return (*p == '\0');
}

int check4()
{
	int i;

	for (i = 0; i < 26; i++)
		if (count2[i] < count1[i]) return 0;

	return 1;
}

int check3()
{
	int i;

	for (i = 0; i < 26; i++)
		if (count1[i] != 0 && count2[i] == 0) return 0;

	return 1;
}

int ispal(char *s)
{
	int i, j, n;

	n = strlen(s);
	if (n <= 1) return 1;

	for (i = 0, j = n - 1; i < j; i++, j--)
		if (s[i] != s[j]) return 0;

	return 1;
}

int check1()
{
	char *p, *q;
	int i, n, k;

	for (p = buf, q = s1, n = 0; *p && islower(*p); n++)
		*q++ = *p++;
	*q = '\0';

	if (n > 1000 || *p++ != ' ')
		return 0;

	if (*p == '+')
		p++;

	if (!isdigit(*p)) return 0;
	while (*p == '0') p++;
	for (n = 0, k = 0; isdigit(*p) && k < 8; k++, p++)
		n = n * 10 + *p - '0';
	if (k >= 8 || n > 1000 || *p++ != ' ') return 0;

	cost_10453 = n;

	for (q = s2, n = 0; *p && islower(*p); n++)
		*q++ = *p++;
	*q = '\0';

	if (*p != '\0' || n > 2000)
		return 0;

	memset(count1, 0, sizeof(count1));
	for (i = 0; s1[i]; i++)
		count1[s1[i] - 'a']++;

	memset(count2, 0, sizeof(count2));
	for (i = 0; s2[i]; i++)
		count2[s2[i] - 'a']++;

	return 1;
}

int main()
{
	int p[8], i, j;

	while (gets(buf)) {
		memset(p, 0, sizeof(p));
		p[1] = check1();
		if (p[1]) {
			p[2] = ispal(s2);
			p[3] = check3();
			p[4] = check4();
			p[5] = check5();
			p[6] = check6();
			p[7] = check7();
		}

		for (i = 1, j = 1; i <= 7; i++) {
			putchar(p[i] ? 'T' : 'F');
			j &= p[i];
		}
		printf(" The solution is %s\n", j ? "accepted" : "not accepted");
	}

	return 0;
}

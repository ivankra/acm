#include <stdio.h>
#include <string.h>

char *s1[] = {
	"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen",
	"yax", "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu",
	NULL
};

char *s2[] = {
	"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat",
	"muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban",
	"eznab", "canac", "ahau"
};

char s[256];

int main()
{
	int t, d, m, y;

	scanf("%d", &t);
	printf("%d\n", t);

	while (t-- > 0 && scanf("%d %*[^A-Za-z] %[A-Za-z] %d", &d, s, &y) >= 3) {
		for (m = 0; s1[m] && strcasecmp(s1[m], s) != 0; m++);
		d += 365 * y + 20 * m;
		printf("%d %s %d\n", 1 + (d % 13), s2[d % 20], d / 260);
	}

	return 0;
}

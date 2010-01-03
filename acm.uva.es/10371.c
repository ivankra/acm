#include <stdio.h>
#include <string.h>

static struct {
	char *name;
	int shift;
} tz[] = {
	{ "UTC", 0 }, { "GMT", 0 }, { "BST", 60 }, { "IST", 60 }, { "WET", 0 },
	{ "WEST", 60 }, { "CET", 60 }, { "CEST", 120 }, { "EET", 120 },
	{ "EEST", 180}, { "MSK", 180 }, { "MSD", 240 }, { "AST", -240 },
	{ "ADT", -180 }, { "NST", -210 }, { "NDT", -150 }, { "EST", -300 }, 
	{ "EDT", -240 }, { "CST", -360 }, { "CDT", -300 }, { "MST", -420 }, 
	{ "MDT", -360 }, { "PST", -480 }, { "PDT", -420 }, { "HST", -600 }, 
	{ "AKST", -540 }, { "AKDT", -480 }, { "AEST", 600 }, { "AEDT", 660 }, 
	{ "ACST", 570 }, { "ACDT", 630 }, { "AWST", 480 }, { NULL, 0 }
};

int main()
{
	char s[1024];
	int i, h, m, n, t;

	scanf("%d", &n);

	while (n-- > 0 && scanf(" %s", s) == 1) {
		if (s[0] == 'n') {
			t = 720;
		} else if (s[0] == 'm') {
			t = 0;
		} else {
			sscanf(s, " %d:%d", &h, &m);
			scanf(" %s", s);
			t = ((h == 12) ? 0 : (h * 60)) + m + ((s[0] == 'p') ? 720 : 0);
		}

		scanf(" %s", s);
		for (i = 0; s[i]; i++)
			if (s[i] >= 'a' && s[i] <= 'z') s[i] &= ~0x20;

		for (i = 0; tz[i].name; i++)
			if (strcmp(tz[i].name, s) == 0) break;

		t -= tz[i].shift;

		scanf(" %s", s);
		for (i = 0; s[i]; i++)
			if (s[i] >= 'a' && s[i] <= 'z') s[i] &= ~0x20;

		for (i = 0; tz[i].name; i++)
			if (strcmp(tz[i].name, s) == 0) break;

		t += tz[i].shift;
		t = (t + 1440) % 1440;

		if (t == 0)
			printf("midnight\n");
		else if (t == 720)
			printf("noon\n");
		else
			printf("%d:%.2d %s\n",
				1 + (((t / 60) + 11) % 12),
				t % 60,
				(t < 720) ? "a.m." : "p.m.");
	}

	return 0;
}

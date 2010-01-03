#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct { char name[32]; int spel; } card[64];

int main()
{
	char *order[64], buf[1024];
	int i, j, k, n;

	while (gets(buf)) {
		if (sscanf(buf, "%d", &n) != 1 || n == 0) break;

		memset(card, 0, sizeof(card));
		for (i = 0; i < n; i++) {
			gets(buf);
			sscanf(buf, " %s ", card[i].name);
			char *p = buf;
			while (*p && !isalpha(*p)) p++;
			while (*p && isalpha(*p)) p++;
			while (*p && *p == ' ') p++;
			card[i].spel = 0;
			while (*p && *p != '\n' && *p != '\r') {
				p++; card[i].spel++;
			}
		}

		for (i = 0; i < n; i++) order[i]="??";

		j = 0;
		for (i = 0; i < n; i++) {
			k = card[i].spel;
			for (;;) {
				if (order[j][0]!='?') { j++; j %= n; continue; }
				k--;
				if (k <= 0) break;
				j++; j %= n;
			}
			order[j] = card[i].name;
		}

		for (i = 0; i < n; i++)
			printf(i ? " %s" : "%s", order[i]);
		printf("\n");
	}

	return 0;
}

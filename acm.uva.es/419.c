#include <stdio.h>
#include <string.h>

int mdays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int wcur, dcur, yday[12][32], ydmonth[512], ydday[512], req_n, req_t;
int busy[65536];

int main()
{
	char s[256];
	int i, j, k, d, m, t1, t2;

	memset(yday, 0, sizeof(yday));
	for (i = k = 0; i < 12; i++) {
		for (j = 0; j < mdays[i]; j++, k++) {
			yday[i][j] = k;
			ydmonth[k] = i;
			ydday[k] = j;
		}
	}

	scanf("%s %d %d %d %d", s, &m, &d, &req_n, &req_t);

	for (wcur = 0; s[0] != "MTWRF"[wcur]; wcur++);
	dcur = yday[m - 1][d - 1];
	req_t /= 15;

	memset(busy, 0, sizeof(busy));
	busy[365 * 32] = 1;

	for (k = wcur, i = 0; i < 365; i++, k = (k + 1) % 7)
		if (k >= 5) for (j = 0; j < 32; j++) busy[i * 32 + j] = 1;

	while (scanf(" %[^\n]", s) == 1 && strcmp(s, "done") != 0) {
		while (scanf(" %s", s) == 1 && strcmp(s, "done") != 0) {
			scanf("%d %d %d %d", &m, &d, &t1, &t2);
			k = 32 * ((yday[m - 1][d - 1] + 365 - dcur) % 365);
			t1 = k + (t1 / 100 - 9) * 4 + (t1 % 100) / 15;
			t2 = k + (t2 / 100 - 9) * 4 + (t2 % 100) / 15;

			for (; t1 < t2; t1++)
				busy[t1] = 1;
		}
	}

	for (k = 0; req_n-- > 0;) {
		for (; k < 11680; k++) {
			for (i = 0; i < req_t && !busy[k + i]; i++)
				if (((k + i) / 32) != (k / 32)) break;
			if (i >= req_t) break;
		}

		if ((k + req_t) > 11680) {
			printf("No more times available\n");
			break;
		}

		printf("%c %d %d %.2d%.2d\n",
			"MTWRF"[(wcur + k / 32) % 7],
			ydmonth[(k / 32 + dcur) % 365] + 1,
			ydday[(k / 32 + dcur) % 365] + 1,
			9 + (k % 32) / 4, (k % 4) * 15);

		k += req_t;
	}

	return 0;
}

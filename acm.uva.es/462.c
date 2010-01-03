#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct { int r, s; } card;

int get(card *a)
{
	while ((a->r = getchar()) != EOF && !isalnum(a->r));
	while ((a->s = getchar()) != EOF && !isalnum(a->s));
	return (a->r != EOF && a->s != EOF);
}

int main()
{
	int s[256], r[256], t[256], i, j, p, q;
	card c[16];

	for (;;) {
		for (i = 0; i < 13 && get(&c[i]); i++);
		if (i < 13) break;

		memset(s, 0, sizeof(s));
		memset(r, 0, sizeof(r));
		memset(t, 0, sizeof(t));

		for (i = 0; i < 13; i++)
			s[c[i].s]++, r[c[i].r]++;

		p = 4 * r['A'] + 3 * r['K'] + 2 * r['Q'] + r['J'];
		for (i = 0; i < 13; i++) {
			if (c[i].r == 'K' && s[c[i].s] <= 1) p--;
			if (c[i].r == 'Q' && s[c[i].s] <= 2) p--;
			if (c[i].r == 'J' && s[c[i].s] <= 3) p--;
		}

		for (q = p, i = 0; i < 4; i++) {
			if (s["SHDC"[i]] == 2) q++;
			if (s["SHDC"[i]] <= 1) q += 2;
		}

		for (i = 0; i < 13; i++) {
			if (c[i].r == 'A') t[c[i].s] = 1;
			if (c[i].r == 'K' && s[c[i].s] >= 2) t[c[i].s] = 1;
			if (c[i].r == 'Q' && s[c[i].s] >= 3) t[c[i].s] = 1;
		}

		for (j = 'S', i = 1; i < 4; i++)
			if (s["SHDC"[i]] > s[j]) j = "SHDC"[i];

		if (p >= 16 && t['S'] && t['H'] && t['D'] && t['C'])
			printf("BID NO-TRUMP\n");
		else if (q < 14)
			printf("PASS\n");
		else
			printf("BID %c\n", j);
	}

	return 0;
}

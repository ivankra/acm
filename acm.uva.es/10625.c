#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MIN_ASCII 32
#define MAX_ASCII 128
#define MAX_RULES 16

typedef unsigned long long u_int64_t;

static u_int64_t counts[256];

struct {
	u_int64_t cnt;
	int ch;
	int inc[256];
} rules[MAX_RULES];

int nr_rules;

static void apply(int times)
{
	register int i, j;
	u_int64_t k;

	while (times-- > 0) {
		for (i = 0; i < nr_rules; i++) {
			rules[i].cnt = counts[rules[i].ch];
			counts[rules[i].ch] = 0;
		}

		for (i = 0; i < nr_rules; i++) {
			k = rules[i].cnt;
			if (k < 1)
				continue;

			for (j = MIN_ASCII; j <= MAX_ASCII; j++)
				if (rules[i].inc[j] > 0)
					counts[j] += rules[i].inc[j] * k;
		}
	}
}

static void print_int64(u_int64_t n)
{
	static char buf[256];
	int i;

	for (i = 0; n != 0 || i == 0; i++, n /= 10)
		buf[i] = '0' + (int)(n % 10);

	while (i-- > 0)
		putchar(buf[i]);

	putchar('\n');
}

int main(void)
{
	int case_no, query_no, i, c, n;

	scanf("%d\n", &case_no);
	while (case_no-- > 0) {
		if (scanf("%d\n", &nr_rules) < 1) break;

		memset(rules, '\0', sizeof(rules));
		for (i = 0; i < nr_rules; i++) {
			do {
				c = getchar();
			} while (c != EOF && (c < MIN_ASCII || c > MAX_ASCII));
			if (c == EOF) break;

			rules[i].ch = c;

			while ((c = getchar()) != EOF && c != '\n' &&
				(c < MIN_ASCII || c > MAX_ASCII || c == '-' || c == '>' || c == ' '));
			while (c != EOF && c != '\n') {
				rules[i].inc[c]++;
				c = getchar();
			}
		}

		if (scanf("%d\n", &query_no) < 1)
			break;

		while (query_no-- > 0) {
			for (i = 0; i < 256; i++)
				counts[i] = 0;

			while ((c = getchar()) != EOF && c != '\n' &&
				(c < MIN_ASCII || c > MAX_ASCII || c == ' '));
			while (c != EOF && c != '\n' && c != ' ') {
				counts[c]++;
				c = getchar();
			}

			while ((c = getchar()) != EOF && c != '\n' &&
				(c < MIN_ASCII || c > MAX_ASCII || c == ' '));

			if (scanf("%d\n", &n) < 1)
				break;

			apply(n);

			print_int64(counts[c]);
		}
	}

	return 0;
}

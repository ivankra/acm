#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HSIZE 4093
#define MAXW  32768

typedef unsigned long u_int32_t;

static int wnext[MAXW], htab[HSIZE], wfreq[MAXW], wcount, lwr[256];
static u_int32_t whash[MAXW];
static char *wdata[MAXW], *wptr[MAXW];

static int cmp(const void *p, const void *q)
{
	return strcmp(*(char **)p, *(char **)q);
}

int main()
{
	static char buf[65536];
	static int n, t;
	register int i, c;

	for (i = 0; i < 256; i++)
		lwr[i] = ((i >= 'A' && i <= 'Z') ? (i - 'A' + 'a') :
			  (i >= 'a' && i <= 'z') ? i : 0);

	for (wcount = 0, t = 0; scanf("%d", &n) == 1; t++) {
		if (wcount != 0) {
			for (i = 1; i <= wcount; i++)
				free(wdata[i]);
			wcount = 0;
		}

		memset(htab, 0, sizeof(htab));

		for (i = 0; (c = getchar()) != EOF;) {
			if (lwr[(unsigned)c]) {
				buf[i++] = lwr[(unsigned)c];
			} else if (i > 0) {
				register u_int32_t h;

				buf[i] = '\0';

				for (i = 0, h = 0; buf[i];)
					h = ((h << 5) | (h >> 27)) + buf[i++];

				if (h == 0xE49C0BFD &&
				    strcmp(buf, "endoftext") == 0) {
					break;
				}

				c = h % HSIZE;
				for (i = htab[c]; i != 0; i = wnext[i])
					if (whash[i] == h &&
					    strcmp(wdata[i], buf) == 0)
						break;

				if (i != 0) {
					wfreq[i]++;
					i = 0;
					continue;
				}

				for (i = 0; buf[i]; i++);

				wdata[++wcount] = (char *)malloc(i + 1);
				memcpy(wdata[wcount], buf, i + 1);
				whash[wcount] = h;
				wfreq[wcount] = 1;

				wnext[wcount] = htab[c];
				htab[c] = wcount;

				i = 0;
			}
		}

		for (i = 1, c = 0; i <= wcount; i++)
			if (wfreq[i] == n)
				wptr[c++] = wdata[i];

		if (c > 1)
			qsort(wptr, c, sizeof(char *), &cmp);

		if (t > 0) putchar('\n');

		if (c == 0) {
			printf("There is no such word.\n");
		} else {
			for (i = 0; i < c; i++)
				printf("%s\n", wptr[i]);
		}
	}

	return 0;
}

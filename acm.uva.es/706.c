#include <stdio.h>

#define HBAR1 1
#define HBAR2 2
#define HBAR3 4
#define LBAR1 8
#define LBAR2 16
#define RBAR1 32
#define RBAR2 64

static const int lcd[10] = {
	HBAR1 | HBAR3 | LBAR1 | LBAR2 | RBAR1 | RBAR2,		/* 0 */
	RBAR1 | RBAR2,						/* 1 */
	HBAR1 | HBAR2 | HBAR3 | RBAR1 | LBAR2,			/* 2 */
	HBAR1 | HBAR2 | HBAR3 | RBAR1 | RBAR2,			/* 3 */
	HBAR2 | LBAR1 | RBAR1 | RBAR2,				/* 4 */
	HBAR1 | HBAR2 | HBAR3 | LBAR1 | RBAR2,			/* 5 */
	HBAR1 | HBAR2 | HBAR3 | LBAR1 | LBAR2 | RBAR2,		/* 6 */
	HBAR1 | RBAR1 | RBAR2,					/* 7 */
	HBAR1 | HBAR2 | HBAR3 | LBAR1 | LBAR2 | RBAR1 | RBAR2,	/* 8 */
	HBAR1 | HBAR2 | HBAR3 | LBAR1 | RBAR1 | RBAR2		/* 9 */
};

int write(int, char *, int);

int main(void)
{
	static char buf[256];
	static int d[16];
	register char *p;
	register int s, k;
	int dn, i;

	while (scanf("%d", &dn) > 0 && dn > 0) {
		s = dn;

		while ((k = getchar()) != EOF && (k < '0' || k > '9'));
		if (k == EOF) break;
		for (dn = 0;;) {
			if (dn < sizeof(d))
				d[dn++] = (int)(k - '0');
			if ((k = getchar()) == EOF || (k < '0' || k > '9'))
				break;
		}
		if (dn == 0) break;

		/*--- HBAR1 ---*/
		for (p = buf, i = 0; i < dn; i++) {
			if (i > 0) *p++ = ' ';
			*p++ = ' ';
			if (lcd[d[i]] & HBAR1)
				for (k = 0; k < s; k++) *p++ = '-';
			else
				for (k = 0; k < s; k++) *p++ = ' ';
			*p++ = ' ';
		}
		*p++ = '\n';
		write(1, buf, (p - buf));

		/*--- LBAR1, RBAR1 ---*/
		for (p = buf, i = 0; i < dn; i++) {
			if (i > 0) *p++ = ' ';
			*p++ = (lcd[d[i]] & LBAR1) ? '|' : ' ';
			for (k = 0; k < s; k++) *p++ = ' ';
			*p++ = (lcd[d[i]] & RBAR1) ? '|' : ' ';
		}
		*p++ = '\n';
		for (i = 0, k = (int)(p - buf); i < s; i++)
			write(1, buf, k);

		/*--- HBAR2 ---*/
		for (p = buf, i = 0; i < dn; i++) {
			if (i > 0) *p++ = ' ';
			*p++ = ' ';
			if (lcd[d[i]] & HBAR2)
				for (k = 0; k < s; k++) *p++ = '-';
			else
				for (k = 0; k < s; k++) *p++ = ' ';
			*p++ = ' ';
		}
		*p++ = '\n';
		write(1, buf, (p - buf));

		/*--- LBAR2, RBAR2 ---*/
		for (p = buf, i = 0; i < dn; i++) {
			if (i > 0) *p++ = ' ';
			*p++ = (lcd[d[i]] & LBAR2) ? '|' : ' ';
			for (k = 0; k < s; k++) *p++ = ' ';
			*p++ = (lcd[d[i]] & RBAR2) ? '|' : ' ';
		}
		*p++ = '\n';
		for (i = 0, k = (int)(p - buf); i < s; i++)
			write(1, buf, k);

		/*--- HBAR3 ---*/
		for (p = buf, i = 0; i < dn; i++) {
			if (i > 0) *p++ = ' ';
			*p++ = ' ';
			if (lcd[d[i]] & HBAR3)
				for (k = 0; k < s; k++) *p++ = '-';
			else
				for (k = 0; k < s; k++) *p++ = ' ';
			*p++ = ' ';
		}
		*p++ = '\n';
		*p++ = '\n';			/* last line */
		write(1, buf, (p - buf));
	}

	return 0;
}

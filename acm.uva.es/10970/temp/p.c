#include <stdio.h>
#include <stdlib.h>

int read(int, char *, int);
int write(int, char *, int);

static char buf[1048576], tmp[16];
static int d[128];

__asm__(".globl _main\n_main: jmp _main1\n");

void proc()
{
	register int i, j;
	register char *p, *q;

	p = q = buf;

	for (;;) {
		while (!d[*p]) p++;
		for (i = *p++ - '0'; d[*p];) i = i * 10 + *p++ - '0';
		p++;
		if (i == 0) break;

		while (!d[*p]) p++;
		for (j = *p++ - '0'; d[*p];) j = j * 10 + *p++ - '0';
		p++;

		i = i * j - 1;

		if (i <= 0) {
			*q++ = '0';
			*q++ = '\n';
		} else {
			for (j = 16; i > 0;) {
				tmp[--j] = i % 10;
				i /= 10;
			}
			while (j < 16) *q++ = tmp[j++] + '0';
			*q++ = '\n';
		}
	}

	write(1, buf, q - buf);
	exit(0);
}

void main1()
{
	int i, j;

	for (i = '0'; i <= '9'; i++) d[i] = 1;

	i = read(0, buf, sizeof(buf));
	buf[i++] = ' '; buf[i++] = '0'; buf[i++] = ' ';

	proc();
}

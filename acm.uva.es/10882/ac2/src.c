#include <stdio.h>
#include <stdlib.h>

int read(int, char *, int);
int write(int, char *, int);

int main2()
{
	static char inbuf[1048576], outbuf[1048576], tmp[256];
	static int isdig[256];
	char *p, *q, *s;
	int l, u, x1, y1, z1, caseid, caseno;

	for (x1 = '0'; x1 <= '9'; x1++) isdig[x1] = 1;

	read(0, p = inbuf, sizeof(inbuf));
	q = outbuf;

#define R(x) {while(!isdig[*p])p++;for(x=*p++-'0';isdig[*p];)x=x*10+*p++-'0';}
#define P(c) {*q++=(c);}
#define W(ex) {int x=(ex);if(x==0){*q++='0';}else{for(s=tmp;x>0;x/=10)*s++=(x%10)+'0';while(s-->tmp)*q++=*s;}}

	R(caseno);

	for (caseid = 1; caseid <= caseno; caseid++) {
		P('C');P('a');P('s');P('e');P(' ');P('#');W(caseid);P(':');P(' ');

		R(x1); R(y1); R(z1);
		if (x1 > 100 || y1 > 100 || z1 > 100)
			goto faulty;

		l = x1 + y1 + z1 - 100;
		if (l <= 0)
			l = 0;
		else
			l = (l + 1) >> 1;

		u = x1;
		if (y1 < u) u = y1;
		if (z1 < u) u = z1;

		if (u < l) goto faulty;

		P('B');P('e');P('t');P('w');P('e');P('e');P('n');P(' ');W(l);
		P(' ');P('a');P('n');P('d');P(' ');W(u);P(' ');P('t');P('i');
		P('m');P('e');P('s');P('.');P('\n');
		continue;

faulty:		P('T');P('h');P('e');P(' ');P('r');P('e');P('c');P('o');P('r');
		P('d');P('s');P(' ');P('a');P('r');P('e');P(' ');P('f');P('a');
		P('u');P('l');P('t');P('y');P('.');P('\n');
	}

	write(1, outbuf, q - outbuf);
	exit(0);
}

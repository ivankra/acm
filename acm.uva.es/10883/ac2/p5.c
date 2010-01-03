#include <stdio.h>
#include <string.h>
#include <math.h>

int read(int, char *, int);
double lgamma(double);

static char inbuf[30*1048576];
static int isdigx[256], isdig[256], n;
static float a[65536];
static double l2;

static double solve()
{
	double c, s;
	int i, j, k, r;

	r = n - 1;
	k = r >> 1;

	if (r & 1) {
		c = exp(lgamma(r + 1) - lgamma(k + 1) - lgamma(r - k + 1) - r * l2);
		for (s = 0., i = k, j = k + 1; i >= 0; i--, j++) {
			s += c * (double)(a[i] + a[j]);
			c *= i / (double)(r - i + 1.);
			if (c < 1e-7) break;
		}
	} else {
		c = exp(lgamma(r + 1) - 2 * lgamma(k + 1) - r * l2);
		s = c * a[k];
		c *= k / (double)(r - k + 1.);
		for (i = k - 1, j = k + 1; i >= 0; i--, j++) {
			s += c * (double)(a[i] + a[j]);
			c *= i / (double)(r - i + 1.);
			if (c < 1e-7) break;
		}
	}

	return s;
}

int main()
{
	char *p;
	int i, c, t;

	l2 = log(2.);

	read(0, p = inbuf, sizeof(inbuf));

	memset(isdig, 0, sizeof(isdig));
	memset(isdigx, 0, sizeof(isdigx));
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;
	for (i = '0'; i <= '9'; i++) isdigx[i] = 1; isdigx['-'] = isdigx['.'] = 1;

#define READU(x) {while(!isdig[*p])p++;for(x=*p++-'0';isdig[*p];)x=x*10+*p++-'0';}

#define READF(z) \
	{ float x,s;while(!isdigx[*p])p++;if(*p=='-'){p++;s=-1.;}else{s=1.;} \
	  for(x=0;isdig[*p];)x=x*10.+(*p++-'0'); \
	  if(*p=='.'){float r=0.1;for(p++;isdig[*p];r/=10.)x+=(*p++-'0')*r;} \
	  z = x * s; }

	READU(t);
	for (c = 1; c <= t; c++) {
		READU(i); n = i;

		for (i = 0; i < n; i++)
			READF(a[i]);

		printf("Case #%d: %.3f\n", c, solve());
	}

	return 0;
}

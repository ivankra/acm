#include <cstdio>
#include <cmath>

int main()
{
	double a,b,c,r,t;
	scanf("%lf%lf%lf%lf%lf",&a,&b,&c,&r,&t);
	r/=10; t=t/10; a-=2*t; b-=2*t; c-=t;
	if (2*r > (a <? b <? c)+1e-9)
		printf("NO\n");
	else
		printf("%.3f\n", (a*b*c-2*acos(0.0)*r*r*r*4/3)/1000.0);
}

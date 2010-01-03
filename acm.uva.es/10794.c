#include <stdio.h>
#include <math.h>

void rd(int v[])
{
	scanf("%d %d %d", &v[0], &v[1], &v[2]);
}

int dot(int a[], int b[])
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

void sub(int a[], int b[])
{
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
}

double eval(int x[], int u[], double c)
{
	double r;
	int i;

	for (r = 0, i = 0; i < 3; i++)
		r += (x[i] + c * u[i]) * (x[i] + c * u[i]);

	return sqrt(r);
}

double solve()
{
	int x[3], x1[3], u[3], u1[3];

	scanf("%*d");
	rd(x); rd(u);
	rd(x1); rd(u1);

	sub(u, x);
	sub(u1, x1);

	sub(x, x1);
	sub(u, u1);

	if (dot(u, u) == 0 || dot(x, u) >= 0)
		return sqrt(dot(x, x));
	else
		return eval(x, u, -dot(x, u) / (double)dot(u, u));
}

int main()
{
	int c, t;

	for (scanf("%d", &t), c = 1; c <= t; c++)
		printf("Case %d: %.4f\n", c, solve());

	return 0;
}

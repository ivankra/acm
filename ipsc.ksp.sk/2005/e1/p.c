#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char s[1024];
unsigned long long d, x;

void solve()
{
	unsigned long long i, a, b, c, dt;

	for (dt = 1, i = 0; i < d; i++)
		dt *= 10LL;

	for (b = 1; b <= dt ; b++) {
//printf("b=%lld d=%lld dt=%lld\n",b,d,dt);

/*a/b=x/dt,  a = b x /dt*/
		a = (b * x) / dt;
		if (a >= 2) a -= 2;

		for (; a < b; a++) {
			c = (a * 2ULL * dt + b) / (2ULL * b);

//printf("a=%lld b=%lld  c=%lld\n", a, b, c);
			if (c == x) {
				printf("%lld %lld\n", a, b);
fflush(stdout);
				return;
			}

			if (c > x)
				break;
		}
	}
fprintf(stderr, "failure x=%lld dt=%lld\n", x, dt);


/*
a/b= x
a = x * b

a/b * 10^d + 0.5 = (a * 2 * 10^d + 1) / (2 * b)
*/

}

int main()
{
	while (scanf(" 0.%[0-9]", s) == 1) {
		d = strlen(s);
		x = atoi(s);

		solve();
	}

	return 0;
}

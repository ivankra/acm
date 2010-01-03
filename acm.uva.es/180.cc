#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int s[1000010], x[1000010];

int main()
{
	s[0] = s[1] = 0;
	for (int i = 2; i <= 1000000; i++)
		s[i] = (s[i-1] + 15) % i;

	memset(x, 0, sizeof(x));

	int a, b, r;
	for (int c = 1; scanf("%d %d", &a, &b) == 2 && (a || b); c++) {
		if (a > b) swap(a, b);

		for (int i = a; i <= b; i++)
			x[s[i]] = x[(i-s[i])%i] = c;

		for (r = 1; r < a && x[r] == c; r++);
		printf( /*???*/2*r<=a/*???*/ ?"%d\n":"Better estimate needed\n", r);
	}
}


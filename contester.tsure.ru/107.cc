#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	char a[4096];
	scanf(" %s", a);

	int s = 0, n = strlen(a);
	for (int i = 0; a[i]; i++)
		s += a[i]-'0';

	for (int r = n-1, t = 0; r >= 0; t += a[r--]-'0') {
		if (a[r] == '9') continue;

		int d = t-1;
		if (d < 0 || d > 9*(n-1-r)) continue;

		a[r]++;
		for (int i = n-1; i > r; d -= a[i--]-'0')
			a[i] = '0'+min(9,d);
		printf("%s\n", a);
		return 0;
	}

	printf("-1\n");
}

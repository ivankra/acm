#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
using namespace std;

typedef long long i64;

int T[32][3], n, m;

int check(i64 a, i64 b, i64 c)
{
	i64 w = a*T[0][0] + b*T[0][1] + c*T[0][2];
	for (int i = 1; i < n; i++)
		if ((a*T[i][0] + b*T[i][1] + c*T[i][2]) > w) return 0;
	return 1;
}

int solve()
{
	m = 0;
	for (int i = 0; i < n; i++) m += T[i][0] + T[i][1] + T[i][2];
	if (n <= 1) return 1;
	for (i64 x = 0, a = 1; x <= 4; x++, a *= m)
		for (i64 y = 0, b = 1; y <= 4; y++, b *= m)
			for (i64 z = 0, c = 1; z <= 4; z++, c *= m)
				if (check(a, b, c)) return 1;
	return 0;
}

int main()
{
	char buf[1024];
	while (scanf("%d", &n) == 1 && n > 0) {
		int canada = 0;
		for (int i = 0; i < n; i++) {
			scanf(" %s %d %d %d", buf, &T[i][0], &T[i][1], &T[i][2]);
			if (strcmp(buf, "Canada") == 0) {
				canada = 1;
				for (int j = 0; j < 3; j++) swap(T[0][j], T[i][j]);
			}
		}
		printf((canada && solve()) ? "Canada wins!\n" : "Canada cannot win.\n");
	}
	return 0;
}

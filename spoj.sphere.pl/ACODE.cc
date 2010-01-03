#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <queue>
using namespace std;

long long ways[6000];
char s[6000];

int main()
{
	while (scanf("%s", s) == 1 && s[0] != '0') {
		int N = strlen(s);

		ways[0] = 1;
		for (int n = 1; n <= N; n++) {
			ways[n] = 0;
			if (s[n-1] != '0')
				ways[n] += ways[n-1];
			if (n >= 2 && s[n-2] != '0' && (s[n-2]-'0')*10 + s[n-1]-'0' <= 26)
				ways[n] += ways[n-2];
		}
		printf("%lld\n", ways[N]);
	}
}

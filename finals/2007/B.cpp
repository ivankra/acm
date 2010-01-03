// ACM ICPC World Finals 2007
// Problem B. Containers.
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int main()
{
	char s[5000];
	for (int cs = 1; scanf(" %s", s) == 1 && strcmp(s, "end") != 0; cs++) {
		int f[5000], res = 0, n = strlen(s);
		f[n] = 0;
		for (int i = n-1; i >= 0; i--) {
			f[i] = 1;
			for (int j = i+1; j < n; j++)
				if (s[j] > s[i]) f[i] = max(f[i], 1 + f[j]);
			res = max(res, f[i]);
		}
		printf("Case %d: %d\n", cs, res);
	}
}

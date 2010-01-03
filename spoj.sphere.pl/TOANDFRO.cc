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
using namespace std;

int main()
{
	int r, c, n;
	char s[1000];
	while (scanf("%d %s", &c, s) == 2 && c > 0) {
		n = strlen(s);
		r = n / c;
		for (int i = 0; i < n; i += 2*c) {
			reverse(s+i+c, s+i+c+c);
		}
		for (int i = 0; i < c; i++)
			for (int j = i; j < n; j += c)
				putchar(s[j]);
		putchar('\n');
	}
}

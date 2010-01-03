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
#include <map>
using namespace std;

int main()
{
	int N;
	while (scanf("%d", &N) == 1 && N > 0) {
		long long value = 0;
		char s[100];
		for (; N >= 1 && scanf(" %[^\n]", s) == 1; N--) {
			int digit = 0;
			for (int i = 0; s[i]; i++)
				if (s[i] == '.') digit++;
				else if (s[i] == '-') digit += 5;
			value = value * (N == 2 ? 18 : 20) + digit;
		}
		printf("%lld\n", value);
	}
}

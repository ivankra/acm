#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

int f(int n) { return n >= 10 ? (n%10 + f(n/10)) : n; }

int main()
{
	int n;
	while (scanf("%d", &n) == 1 && n > 0) {
		while (n >= 10) n = f(n);
		printf("%d\n", n);
	}
}

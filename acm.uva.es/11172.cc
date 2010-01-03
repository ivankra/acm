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

int main() {
	int T;
	scanf("%d", &T);

	long long a, b;
	for (int cs = 1; cs <= T && scanf("%lld %lld", &a, &b) == 2; cs++) {
		if (a > b) printf(">\n");
		else if (a == b) printf("=\n");
		else printf("<\n");
	}
}

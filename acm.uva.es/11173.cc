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

	int n, k;
	for (int cs = 1; cs <= T && scanf("%d %d", &n, &k) == 2; cs++) {
		printf("%d\n", k ^ (k >> 1));
	}
}

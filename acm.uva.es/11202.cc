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
	int T, n, m;

	scanf("%d", &T);
	for (int cs = 1; cs <= T && scanf("%d %d", &n, &m) == 2; cs++) {
		if (n != m) {
			printf("%d\n", ((n+1)/2) * ((m+1)/2));
		} else {
			int k = (n+1)/2;
			printf("%d\n",  (k*k-k)/2+k);
		}
	}
}

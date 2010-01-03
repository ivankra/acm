#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

int N, p[1000100];
char s[1000100];

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d %s", &N, s) == 2; cs++) {
		assert(N >= 2);

		p[0] = p[1] = 0;
		int m = 2, k = 0;
		for (;;) {
			if (s[m-1] == s[k]) {
				p[m] = ++k;
				if (++m > N) break;
			} else if (k == 0) {
				p[m] = 0;
				if (++m > N) break;
			} else {
				k = p[k];
			}
		}

		printf("Test case #%d\n", cs);
		//for (int m = 1; m <= N; m++) printf("%c %d\n", s[m-1], p[m]);
		for (int m = 1; m <= N; m++) {
			if (2*p[m] >= m && m % (m-p[m]) == 0) {
				printf("%d %d\n", m, m/(m-p[m]));
			}
		}
		printf("\n");
	}
}

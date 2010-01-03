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
	char buf[1000];

	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf(" %s", buf);

		int x = 0, y = 0, z = 0;
		char *s = buf;

		while (*s == '?') { x++; s++; }
		if (*s++ != 'M') goto no;
		while (*s == '?') { y++; s++; }
		if (*s++ != 'E') goto no;
		while (*s == '?') { z++; s++; }
		if (*s != 0 && *s != '\r' && *s != '\n') goto no;

		if (x+y == z && x >= 1 && y >= 1) {
			printf("theorem\n"); continue;
		}
no:		printf("no-theorem\n");
	}
}

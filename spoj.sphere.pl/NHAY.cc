// KMP
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
#include <set>
using namespace std;

int m, *p;
char buf[100], *needle;

int main()
{
	while (gets(buf)) {
		if (sscanf(buf, "%d", &m) != 1) break;

		needle = new char[m+10];
		gets(needle);

		p = new int[m+10];
		p[0] = p[1] = 0;
		for (int i = 2, j = 0; i <= m; i++) {
			while (j > 0 && needle[j] != needle[i-1]) j = p[j];
			if (needle[j] == needle[i-1]) j++;
			p[i] = j;
		}

		for (int i = 0, j = 0;; i++) {
			int c = getchar();
			if (c == '\n') break;

			while (j > 0 && needle[j] != c) j = p[j];
			if (needle[j] == c) j++;

			if (j == m) {
				printf("%d\n", i-m+1);
				j = p[m];
			}
		}
		printf("\n");

		delete[] p;
		delete[] needle;
	}
}

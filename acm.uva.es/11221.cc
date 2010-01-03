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

bool check(char *s, int k)
{
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			char c = s[i*k+j];
			if (s[j*k+i] != c) return false;
			if (s[(k-1-i)*k+(k-1-j)] != c) return false;
			if (s[(k-1-j)*k+(k-1-i)] != c) return false;
		}
	}
	return true;
}

int main() {
	static char s[50000];
	gets(s);

	int T;
	sscanf(s, "%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		gets(s);

		int n = 0;
		for (int i = 0; s[i]; i++)
			if (isalpha(s[i])) s[n++] = tolower(s[i]);

		int k = 0;
		for (k = 0; k*k < n; k++);

		printf("Case #%d:\n", cs);
		if (k*k != n || !check(s, k)) {
			printf("No magic :(\n");
		} else {
			printf("%d\n", k);
		}
	}
}

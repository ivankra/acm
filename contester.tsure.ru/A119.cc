#include <cstdio>
#include <cstdlib>
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
	int N;
	char s[10];

	scanf("%d %s", &N, s);

	printf("%c\n", s[2]);
	for (int i = 2; i < N; i++) {
		putchar(s[0]);
		for (int j = 2; j < i; j++) putchar('.');
		printf("%c\n", s[2]);
	}

	putchar(s[0]);
	for (int i = 1; i < N; i++) putchar(s[1]);
	putchar('\n');	
}

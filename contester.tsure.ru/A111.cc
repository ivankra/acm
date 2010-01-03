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
	int c;
	while ((c = getchar()) != EOF) {
		if (c == '/') putchar('\n');
		else if (c == '+' || c == '-') putchar(c);
	}
	putchar('\n');
}

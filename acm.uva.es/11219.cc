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

	for (int cs = 1; cs <= T; cs++) {
		printf("Case #%d: ", cs);

		struct Date { int m, d, y; } a, b;
		scanf("%d / %d / %d", &b.d, &b.m, &b.y);
		scanf("%d / %d / %d", &a.d, &a.m, &a.y);

		int age = b.y - a.y;
		if (b.m < a.m || (b.m == a.m && b.d < a.d))
			age--;

		if (age < 0)
			printf("Invalid birth date\n");
		else if (age > 130)
			printf("Check birth date\n");
		else
			printf("%d\n", age);
	}
}

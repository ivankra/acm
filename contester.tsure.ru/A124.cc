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

int cvt(string A, int base) {
	long long res = 0;
	for (int i = 0; i < (int)A.size(); i++) {
		if (res > (1LL << 32)) return -1;

		int d;
		if (isdigit(A[i])) d = A[i] - '0';
		else if (isalpha(A[i])) d = toupper(A[i]) - 'A' + 10;
		else return -1;

		if (d >= base) return -1;

		res = res * base + d;
	}
	return res;
}

int main()
{
	string A;
	int B;

	cin >> A >> B;

	int X = 2;
	while (X <= 36 && cvt(A, X) != B) X++;

	printf("%d\n", X <= 36 ? X : 0);
}

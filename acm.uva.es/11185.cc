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
	int N;
	while (scanf("%d", &N) == 1 && N >= 0) {
		string s = "";
		while (N > 0 || s.size() == 0) {
			s = (char)('0' + N%3) + s;
			N /= 3;
		}
		printf("%s\n", s.c_str());
	}
}

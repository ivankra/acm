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
	int G;
	char S[1024];

	while (scanf("%d %s", &G, S) == 2 && G > 0) {
		int N = strlen(S);
		for (int i = 0; i+N/G <= N; i += N/G)
			reverse(S+i, S+i+N/G);
		printf("%s\n", S);
	}
}

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

int f(int w, int h) {
	return max(min(w/4, h), min(w,h)/2);
}

int main() {
	int N, w, h;

	while (scanf("%d", &N) == 1 && N > 0) {
		int best = 1, best_size = -1;
		for (int i = 1; i <= N; i++) {
			scanf("%d %d", &w, &h);
			int r = max(f(4*w, 4*h), f(4*h, 4*w));
			if (r > best_size) {
				best_size = r;
				best = i;
			}
		}
		printf("%d\n", best);
	}
}

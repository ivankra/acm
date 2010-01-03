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

int num[50], target;
struct History { int a, op, b, c; } history[50];

bool rec(int N, int K, int v[]) {
	int v1[8];

	int eq[8], marked[8];
	for (int i = 0; i < N; i++) {
		eq[i] = 0;
		for (int j = 0; j < N; j++)
			if (v[i] == v[j]) eq[i] |= 1 << j;
	}

	History &h = history[K];
	for (int op_i = 0; op_i < 4; op_i++) {
		h.op = "+x-/"[op_i];

		for (int i = 0; i < N; i++) marked[i] = 0;

		for (int mi = 0; mi < N; mi++) {
			for (int ma = mi+1; ma < N; ma++) {
				int a = v[mi], b = v[ma];

				if (marked[ma] & (1 << mi)) continue;
				if (marked[mi] & (1 << ma)) continue;
				for (int i = 0; i < N; i++)
					if (v[i] == v[mi]) marked[i] |= eq[ma];

				if (a < b) swap(a, b);

				long long c = -1;
				if (op_i == 0) c = a + b;	
				else if (op_i == 1) c = a * (long long)b;
				else if (op_i == 2) c = a - b;
				else if ((a % b) == 0) c = a / b;

				if (c <= 0 || c > 1600000000) continue;

				h.a = a;
				h.b = b;
				h.c = (int)c;
				if (K == 1) {
					if (c == target) return true;
				} else {
					int j = 0;
					v1[j++] = c;
					for (int i = 0; i < mi; i++) v1[j++] = v[i];
					for (int i = mi+1; i < ma; i++) v1[j++] = v[i];
					for (int i = ma+1; i < N; i++) v1[j++] = v[i];
					if (rec(N-1, K-1, v1)) return true;
				}
			}
		}
	}

	return false;
}

int main() {
	int N;
	while (scanf("%d %d", &target, &N) == 2 && target > 0) {
		for (int i = 0; i < N; i++)
			scanf("%d", &num[i]);

		int k;
		for (k = 1; k <= N-1; k++)
			if (rec(N, k, num)) break;

		if (k > N-1) {
			printf("No solution\n");
		} else {
			for (int i = k; i >= 1; i--) {
				History h = history[i];
				printf("%d %c %d = %d%s\n", h.a, h.op, h.b, h.c, i==1 ? " <-" : "");
			}
		}
	}
}

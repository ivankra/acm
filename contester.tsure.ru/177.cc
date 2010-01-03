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
typedef unsigned char byte;

int L[2000010], N, Q;

int main() {
	scanf("%d %d", &N, &Q);

	for (int i = 1; i <= N; i++) {
		int prev = (i == 1 ? N : (i-1));
		int next = (i == N ? 1 : (i+1));
		L[i] = prev ^ next;
	}

	int cur = 1, next = 2, dir = 1;
	while (N > 1) {
		for (int i = 1; i < Q; i++) {
			if (dir > 0) {
				int nn = L[next] ^ cur;
				cur = next;
				next = nn;
			} else {
				int p = L[cur] ^ next;
				next = cur;
				cur = p;
			}
		}

		if (N == 2) { cur = next; break; }

		int p = L[cur] ^ next;
		int pp = L[p] ^ cur;
		int nn = L[next] ^ cur;

		L[p] = pp ^ next;
		L[next] = p ^ nn;

		cur = next;
		next = nn;
		
		N--;

		dir = (cur & 1) ? +1 : -1;
	}

	printf("%d\n", cur);
}

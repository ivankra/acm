#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;
typedef long long int64;

struct SwappingCats {
	int Abuf[10000], *A, nwhite, nblack, S;
	string res;

	void dump() {
		for (int i = -nwhite; i <= nblack; i++) putchar(A[i]);
		printf("\n");
	}

	void move(int x, int y) {
		assert(A[x] != '_'); assert(A[y] == '_');
		swap(A[x], A[y]);
		S = x;

		if (x == y+1) res += '1';
		else if (x == y-1) res += '2';
		else if (x == y+2) res += '3';
		else res += '4';

		//printf("move(%d, %d): ", x, y); dump();
	}

	string swapCats(int W, int B) {
		nwhite = W;
		nblack = B;

		memset(Abuf, 0, sizeof(Abuf));
		A = &Abuf[5000];
		for (int i = -W, j = 1; i <= B; i++) {
			if (i != 0) {
				A[i] = (i < 0 ? 'W' : 'B');
			} else {
				A[i] = '_';
				S = i;
			}
		}

		res = "";

		for (;;) {
			int k = 0;
			if (A[S-1] == 'W') { move(S-1, S); k++; }
			while (A[S+1] == 'W' && A[S+2] == 'B') { move(S+2, S); k++; }
			if (A[S+1] == 'B') { move(S+1, S); k++; }
			while (A[S-2] == 'W' && A[S-1] == 'B') { move(S-2, S); k++; }
			if (k == 0) break;
		}

		return res;
	}
};

#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define MAX 1048576

unsigned char input[MAX];
int a[MAX], b[MAX], N;

int main()
{
	for (N = 0;;) {
		int c = getchar();
		if (c == EOF) break;
		assert(N+5 < MAX);
		input[N++] = (unsigned char)c;
	}

	a[N] = 0;
	for (int i = N-1; i >= 0; i--) {
		a[i] = 2 + a[i+1];
		b[i] = 1;

		for (int j = 1; j <= 128 && i+j <= N; j++) {
			if (1+j+a[i+j] < a[i]) {
				a[i] = 1 + j + a[i+j];
				b[i] = j;
			}
		}

		for (int j = 2; j <= 128 && i+j <= N && input[i+j-1] == input[i]; j++) {
			if (2 + a[i+j] < a[i]) {
				a[i] = 2 + a[i+j];
				b[i] = -j;
			}
		}
	}

	for (int i = 0; i < N;) {
		int k = b[i];
		if (k > 0) {
			putchar(k-1);
			for (int j = 0; j < k; j++) putchar(input[i+j]);
			i += k;
		} else {
			putchar(127 - k);
			putchar(input[i]);
			i += -k;
		}
	}
}

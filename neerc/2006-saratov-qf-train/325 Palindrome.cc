#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

const int MaxN = 1048576;

long long inv(int *a, int N) {
	if (N <= 64) {
		int res = 0;
		for (int k = 1; k < N; k++) {
			int i, t = a[k];
			for (i = k-1; i >= 0 && a[i] > t; i--) {
				a[i+1] = a[i];
				res++;
			}
			a[i+1] = t;
		}
		return res;
	}

	int n1 = N/2, n2=N-n1;
	int *b = a + n1;

	long long res = inv(a, n1) + inv(b, n2);
	int i = 0, j = 0;

	static int tmp[MaxN];
	int m = 0;

	while (i < n1 && j < n2) {
		if (a[i] < b[j]) {
			res += j;
			tmp[m++] = a[i++];
		} else {
			tmp[m++] = b[j++];
		}
	}

	while (i < n1) { res += j; tmp[m++] = a[i++]; }
	while (j < n2) tmp[m++] = b[j++];

	for (i = 0; i < N; i++) a[i] = tmp[i];
	return res;
}

long long trans(char *src, char *dst, int N) {
	static int pos[MaxN], arr[MaxN], idx[256], cum[256];
	for (int i = 0; i < 256; i++) idx[i] = cum[i] = 0;

	for (int i = 0; i < N; i++) cum[src[i]]++;
	for (int i = 1; i < 256; i++) cum[i] += cum[i-1];

	for (int i = 0; i < N; i++) {
		int c = cum[src[i]-1] + idx[src[i]];
		idx[src[i]]++;
		pos[c] = i;
	}

	for (int i = 0; i < 256; i++) idx[i] = 0;
	for (int i = 0; i < N; i++) {
		int c = cum[dst[i]-1] + idx[dst[i]];
		idx[dst[i]]++;
		arr[i] = pos[c];
	}

//	printf("arr: ");for (int i = 0; i < N; i++) printf("%d ", arr[i]);printf("\n");
	long long res = inv(arr, N);
//	printf("tranforming %.*s to %.*s => %lld\n", N,src, N,dst, res);
	return res;
}

long long solve(char *src, int N) {
	static char dst[MaxN+1];

	int cnt[256];
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < N; i++)
		cnt[src[i]]++;

	int odd = 0;
	for (int c = 'A'; c <= 'Z'; c++) {
		if ((cnt[c] % 2) == 1) {
			if (odd != 0) return -1;
			odd = c;
		}
	}

	if ((N % 2) == 1)
		dst[(N-1)/2] = odd;

	int idx[256], left = 0, right = (N+1)/2;
	memset(idx, 0, sizeof(idx));

	for (int i = 0; i < N; i++) {
		if (src[i] == odd && 2*idx[odd]+1 == cnt[odd]) {
			;
		} else if (2*idx[src[i]] < cnt[src[i]]) {
			dst[left++] = src[i];
		} else {
			dst[right++] = src[i];
		}
		idx[src[i]]++;
	}
	dst[N] = 0;

	long long res = trans(src, dst, N);
	reverse(dst, dst+left);
	res += trans(dst, dst+(N+1)/2, N/2);
	return res;
}

int main()
{
	static char src[MaxN+1];
	int N;

	for (N = 0;;) {
		int c = getchar();
		if (c == EOF) break;
		if (isalpha(c)) src[N++] = toupper(c);
	}
	src[N] = 0;

	printf("%lld\n", solve(src, N));
}

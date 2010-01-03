#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

// Randomized quicksort
template<typename T>
void quicksort(T a[], int n)
{
	int i, j;
	T x;

	while (n > 20) {
		// Choose pivot
		x = a[rand() % n];

		// Partitioning
		i = -1; j = n;
		while (true) {
			while (a[++i] < x);
			while (x < a[--j]);
			if (i >= j) break;
			swap(a[i], a[j]);
		}
		if (j != n-1) j++;

		// Now a[0..j-1] <= x, a[j..n-1] >= x, 1<=j<=n-1.

		// Recursively sort the smaller array, and iteratively the larger one.
		if (j < n-j) {
			quicksort(a, j);
			a += j;
			n -= j;
		} else {
			quicksort(a+j, n-j);
			n = j;
		}
	}

	// Insertion sort
	for (i = 1; i < n; i++) {
		x = a[i];
		for (j = i; j > 0 && x < a[j-1]; j--)
			a[j] = a[j-1];
		a[j] = x;
	}
}

// Helper procedure for heapsort
template<typename T>
void heapify(T a[], int n, int i)
{
	int j;
	while ((j = 2 * i) <= n) {
		if (j+1 < n && a[j] < a[j+1]) j++;
		if (a[j] < a[i]) break;
		swap(a[i], a[j]);
		i = j;
	}
}

// Heapsort
template<typename T>
void heapsort(T a[], int n)
{
	a--;

	for (int i = n/2; i >= 1; i--)
		heapify(a, n, i);

	while (n > 1) {
		swap(a[1], a[n]);
		n--;
		heapify(a, n, 1);
	}
}

// LSD radix sort for 32-bit non-negative integers
void radixsort(int *input, int n)
{
	enum { r = 12, k = 1 << r };
	int c[k];

	int *a = input, *b = new int[n];

	for (int shift = 0; shift < 32; shift += r) {
		for (int i = 0; i < k; i++) c[i] = 0;
		for (int i = 0; i < n; i++) ++c[(a[i] >> shift) & (k - 1)];
		for (int i = 1; i < k; i++) c[i] += c[i-1];
		for (int i = n-1; i >= 0; i--) b[--c[(a[i] >> shift) & (k - 1)]] = a[i];
		swap(a, b);
	}

	if (a != input) { memcpy(input, a, n * sizeof(int)); swap(a, b); }
	delete[] b;
}


int main()
{
	for (int cs = 1; cs <= 10; cs++) {
		if (cs % 10000 == 0) printf("%d\n", cs);

		int n = 1000000;
		vector<int> a(n), b, c;
		for (int i = 0; i < n; i++) a[i] = rand();

		printf("n=%d ", a.size());

		{ c = a; int t = clock(); sort(&c[0], &c[0] + n); t = clock() - t; printf("std::sort=%d ", t); }

		{ b = a; int t = clock(); quicksort(&b[0], n); t = clock() - t; printf("quicksort=%d ", t); }
		for (int i = 0; i < n; i++) assert(c[i] == b[i]);

		{ b = a; int t = clock(); radixsort(&b[0], n); t = clock() - t; printf("radixsoft=%d ", t); }
		for (int i = 0; i < n; i++) assert(c[i] == b[i]);

		{ b = a; int t = clock(); heapsort(&b[0], n); t = clock() - t; printf("heapsort=%d\n", t); }
		for (int i = 0; i < n; i++) assert(c[i] == b[i]);
	}
}

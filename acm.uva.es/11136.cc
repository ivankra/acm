#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

void reduce(int a[], int &n) {
	if (n > 10020) {
		int i = 5005;
		int j = n - 5005;
		assert(i < j);
		while (j < n) a[i++] = a[j++];
		n = i;
	}
}

int main() {
	static int A[1000100], x[1000100], y[1000100];
	int n1, n2, N, ndays;

	while (scanf("%d", &ndays) == 1 && ndays != 0) {
		assert(1 <= ndays && ndays <= 5000);

		long long res = 0;
		N = 0;

		for (int day = 0; day < ndays; day++) {
			int i, j;

			scanf("%d", &n1);
			for (j = 0; j < n1; j++)
				scanf("%d", &x[j]);
			sort(x, x+n1);
			reduce(x, n1);

			for (i = 0; i < N; i++)
				y[i] = A[i];
			n2 = N;

			if (n1 == 0 && n2 == 0) continue;

			int low;
			i = 0; j = 0;
			if (n2 == 0 || (n1 >= 1 && x[0] < y[0])) {
				low = x[0];
				i++;
			} else {
				low = y[0];
				j++;
			}

			N = 0;
			while (i < n1 && j < n2) {
				if (x[i] < y[j])
					A[N++] = x[i++];
				else
					A[N++] = y[j++];
			}
			while (i < n1) A[N++] = x[i++];
			while (j < n2) A[N++] = y[j++];
			reduce(A, N);

			int high = A[--N];
			res += high - low;

//printf("day %d: high=%d low=%d  remains:", day, high, low);
//for(i=0;i<N;i++)printf(" %d",A[i]);printf("\n");

		}

		printf("%lld\n", res);
	}
}

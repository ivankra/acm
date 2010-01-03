#include <cstdio>

int main()
{
	int N;
	scanf("%d", &N);

	unsigned *a = new unsigned[N];
	unsigned long long mean = 0, aux = 0;

	for (int i = 0; i < N; i++) {
		scanf("%u", &a[i]);
		mean += a[i];
	}

        if (mean % (unsigned)N != 0) {
        	printf("NO SOLUTION\n");
        } else {
        	mean /= (unsigned)N;
		for (int i = 0; i < N; i++)
			if (a[i] > mean) aux += a[i] - mean;
		printf("%llu %llu\n", mean, aux);
	}
}

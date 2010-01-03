#include <cstdio>

long long a[1000];
int N;

int clerkId[1000];

bool check(long long maxWork, int K, bool print) {
    long long s = 0;
    for (int i = N-1; i >= 0; i--) {
        if (a[i] > maxWork) return false;

        if (s + a[i] > maxWork || i+1 < K) {
            s = 0;
            if (--K <= 0) return false;
        }

        clerkId[i] = K;
        s += a[i];
    }

    if (print) {
        for (int i = 0; i < N; i++) {
            if (i != 0) {
                if (clerkId[i-1] != clerkId[i])
					printf(" / ");
                else
					printf(" ");
            }
			printf("%lld", a[i]);
        }
		printf("\n");
    }

    return true;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		int K;
		scanf("%d %d", &N, &K);

        for (int i = 0; i < N; i++)
			scanf("%lld", &a[i]);

        long long left = 0, right = 6000000000LL;
        while (right - left > 1) {
            long long mid = (left + right) / 2;
            if (check(mid, K, false))
                right = mid;
            else
                left = mid;
        }

        check(right, K, true);
    }
}

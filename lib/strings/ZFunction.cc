#include <cstdio>
#include <vector>
#include <string>
using namespace std;

// Computes z-function for string s.  Time complexity: O(n).
// Return values: z[i] = maximum k, such that s[i..i+k-1] = s[0..k-1].
// Application: pattern-matching - to find S in T, compute z-fun for S$T
vector<int> zfun(const char *s)
{
	int N = strlen(s), a=0, b=0;
	vector<int> z(N, N);
	for (int i = 1; i < N; i++) {
		int k = i < b ? min(b-i, z[i-a]) : 0;
		while (i+k < N && s[i+k] == s[k]) ++k;
		z[i] = k;
		if (i+k > b) { a=i; b=i+k; }
	}
	return z;
}


int main() {
	for (int cs = 1; cs <= 1000; cs++) {
		int N = 1 + rand() % 100000;
		printf("Test %d: N=%d ", cs, N); fflush(stdout);

		string s(N, 'a');
		for (int i = 0; i < N; i++)
			s[i] = 'a' + rand() % 2;

		vector<int> z = zfun(s.c_str());
		printf(". "); fflush(stdout);

		for (int i = 0; i < N; i++) {
			int k = 0;
			for (k = 0; i+k < N && s[k] == s[i+k]; k++);

			if (z[i] != k) {
				printf("*FAILED*\n");
				printf("s=%s\n", s.c_str());
				printf("z=");
				for (int j = 0; j < N; j++)
					printf("%d ", z[j]);
				printf("\n");
				printf("z[%d] must be %d\n", i, k);
				return 1;
			}
		}
		printf("ok\n");
	}
}

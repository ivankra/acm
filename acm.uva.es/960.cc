#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		int a, b;
		scanf("%d %d", &a, &b);

		a = abs(a);
		b = abs(b);

		int n = a * a + b * b;

		for (int c = 0; c <= 150; c++) {
			for (int d = 0; d <= 150; d++) {
				int m = c * c + d * d;
				if (m <= 1 || m >= n) continue;

				if ((a*c+b*d)%m==0 && (b*c-a*d)%m==0) {
					printf("C\n");
					goto done;
				}
			}
		}

		printf("P\n");
done:;
	}

	return 0;
}

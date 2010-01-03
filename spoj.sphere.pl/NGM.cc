#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int N;
	scanf("%d", &N);

	if (N % 10 == 0) {
		printf("2\n");
	} else {
		printf("1\n%d\n", N % 10);
	}
}

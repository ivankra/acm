#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++)
		printf("no\n");
}

/*
x_n = (1000^n - 1) / 999

n=3k: divisible by 3
n=2k: divisible by 7, 11, 13
n=3k+1: divisible by 43
n=6k+5: divisible by 31
*/


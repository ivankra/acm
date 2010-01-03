#include <stdio.h>
#include <math.h>

int nums[65536];

int recur(int i, int j, int N)
{
	if (i < 0 || j < 0 || i >= N || j >= N)
		return 0;

	if (i < j) {
		return (nums[i] > nums[j]) + recur(i, j + 1, N);
	} else if (i > j) {
		return (nums[i] > nums[j]) + recur(i, j - 1, N);
	} else {
		int t;
		t = recur(i + 1, j + 1, N);
		t += (nums[i] > nums[j]) + recur(i, j + 1, N);
		t += (nums[i] > nums[j]) + recur(i, j - 1, N);
		return t;
	}
}

int main(void)
{
	int i, n, c;

	for (c = 1; scanf("%d", &n) == 1 && n > 0; c++) {
		for (i = 0; i < n; i++)
			scanf("%d", &nums[i]);
		printf("Case %d: %d\n", c, recur(0, 0, n));
	}

	return 0;
}

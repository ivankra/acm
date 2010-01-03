#include <stdio.h>
#include <string.h>
#include <assert.h>

int ans[2048], dish_s[2048], dish_g[2048], rate1, rate2, denom, n;
int cost1, cost2;

int gcd(int x, int y) { return (y == 0) ? x : gcd(y, x % y); }

void sim()
{
	static int get_tm[2048], get_fd[2048];
	int i, j, k, tm, left;

	memset(ans, 0, sizeof(ans));

	denom = (rate1 / gcd(rate1, rate2)) * rate2;
	rate1 = denom / rate1;
	rate2 = denom / rate2;

	for (tm = 0, i = 0; i < n; i++) {
		tm += dish_g[i] * rate1;
		get_tm[i] = tm;
		get_fd[i] = (dish_s[i] - dish_g[i]) * rate2;
	}

	get_tm[n] = 0x7FFFFFFF;
	for (tm = 0, left = 0, i = 0; i < n; i++) {
		tm = get_tm[i];
		left += get_fd[i];

		while (tm < get_tm[i+1] && left > 0) {
			j = tm / denom; if (j > 2000) return;
			if ((tm % denom) == 0 || (tm / denom) > (get_tm[i] / denom))
				ans[j] = 1;

			tm += rate2; left -= rate2;

			j = tm / denom; if (j > 2000) return;
			if ((tm % denom) == 0 || (tm / denom) > (get_tm[i] / denom))
				ans[j] = 1;
		}
	}
}

void sol()
{
	int i, x, nq;

	scanf("%d %d %d %d", &rate1, &rate2, &n, &nq);
	for (i = 0; i < n; i++)
		scanf("%d %d", &dish_s[i], &dish_g[i]);

	sim();

	while (nq-- > 0 && scanf("%d", &x) == 1) {
		assert(0 <=x && x <= 2000);
		printf((ans[x]) ? "full\n" : "clear\n");
	}
}

int main()
{
	int t;

	for (scanf("%d", &t); t-- > 0;) {
		sol();
		if (t) printf("\n");
	}

	return 0;
}

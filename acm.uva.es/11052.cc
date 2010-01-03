#include <cstdio>

int main() {
	struct Rec { int time, need, year; } R[1024];
	int n;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (int i = 0; i < n; i++) {
			int mon, day, hr, mn; char flag;
			scanf(" %d : %d : %d : %d %*s %c", &mon, &day, &hr, &mn, &flag);
			R[i].time = ((mon*100+day)*100+hr)*100+mn;
			R[i].need = (flag == '+');
		}

		R[n-1].year = 0;
		for (int i = n-2; i >= 0; i--)
			R[i].year = R[i+1].year - (R[i].time < R[i+1].time ? 0 : 1);

		int f[1024] = { 1 };
// f[m] = min solution for up to R[m]th record, AND preserving it

		int needed = R[0].need;
		for (int m = 1; m < n; m++) {
			f[m] = f[m-1] + 1;
			if (needed == 0) f[m] = 1;

			for (int p = m-1; p >= 0; p--) {
				// discard records R[p+1] ... R[m-1]

				int y = R[m].year - (R[p].time < R[m].time ? 0 : 1);
				if (y != R[p].year) break;

				f[m] <?= f[p] + 1;
				if (R[p].need) break;
			}

			needed += R[m].need;
		}

		int res = f[n-1];
		for (int i = n-1; i >= 0 && R[i].year == 0; i--) {
			res <?= f[i];
			if (R[i].need) break;
		}

		if (needed == 0) res = 0;

		printf("%d\n", res);
	}
}

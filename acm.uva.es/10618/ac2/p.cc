#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

char line[128], *btn = "ULDR.";
int memo[72][4][4][4];

int f(int tm, int left, int right, int prev, int recov=0) {
	int &ret = memo[tm][left][right][prev];

	if (!recov) {
		if (ret != -1) return ret;
		ret = 1 << 30;
	}

	if (line[tm] == '\0' || strchr(btn, line[tm]) == NULL) {
		if (recov) printf("\n");
		return ret = 0;
	}

	int now = strchr(btn, line[tm]) - btn;

	if (now == 4) {
		int x = f(tm+1, left, right, 0);
		ret <?= x;
		if (recov && ret == x) {
			putchar('.');
			return f(tm+1, left, right, 0, 1);
		}
	}

	for (int foot = 1; foot <= 2; foot++)
	for (int to = 0; to < 4; to++) {
		if (now < 4 && to != now) continue;

		if (foot == 1 && to == right) continue;
		if (foot == 2 && to == left) continue;

		int pos = (foot == 1 ? left : right);
		int shift = min((to - pos + 4) % 4, (pos - to + 4) % 4);

		if (shift > 0) {
			if (foot == 1 && right == 1) continue;
			if (foot == 2 && left == 3) continue;
		}

		int x = (prev != foot ? 1 : ("357"[shift] - '0'));
		if (foot == 1)
			x += f(tm+1, to, right, foot);
		else
			x += f(tm+1, left, to, foot);

		if (!recov || ret != x) {
			ret <?= x;
			continue;
		}

		putchar(".LR"[foot]);
		if (foot == 1)
			return f(tm+1, to, right, foot, 1);
		else
			return f(tm+1, left, to, foot, 1);
	}

	return ret;
}

int main()
{
	while (gets(line) && line[0] != '#') {
		memset(memo, 0xff, sizeof(memo));
		for (int r = 0; r < 2; r++) f(0, 1, 3, 0, r);
	}
}

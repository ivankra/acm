#include <cstdio>
#include <cassert>
#include <cstring>

char orig[100];
int pos;
long long out[10], pw[100];

void doit(int p) {
	for (int d = 0; d <= 9 && d <= orig[p]-'0'; d++) {
		if (d < orig[p]-'0') {
			long long m = pw[8-p];

			if (pos < p) {
				out[orig[pos]-'0'] += m;
			} else if (pos == p) {
				out[d] += m;
			} else {
				for (int i = 0; i <= 9; i++)
					out[i] += m/10;
			}
		} else {
			doit(p+1);
		}
	}
}

void solve() {
	memset(out, 0, sizeof(out));

	long long low = (orig[2] == '0') ? 1 : 0;
	long long up = 0;
	for (int i = 0; i < 10; i++)
		if (i != 2) up = up * 10LL + (long long)(orig[i] - '0');

	if (up <= low) return;
	if (pos == 2) { out[orig[2]-'0'] = up - low; return; }

	if (pos > 2) pos--;
	for (int i = 2; i < 10; i++)
		orig[i] = orig[i+1];

	doit(0);

	if (low == 1 && out[0] > 0) out[0]--;
}

int main()
{
	pw[0] = 1;
	for (int n = 1; n < 20; n++)
		pw[n] = pw[n-1] * 10LL;

	for (int cs = 0; scanf(" %[0-9] %d", orig, &pos) == 2; cs++) {
		assert(strlen(orig) == 10 && 0 <= pos && pos <= 10);
		if (strcmp(orig, "0000000000") == 0) {
			assert(pos == 0);
			break;
		}
		assert(pos != 0);
		pos--;

		solve();

		if (cs > 0) printf("\n");
		for (int i = 0; i <= 9; i++)
			printf("%11lld\n", out[i]);
	}
}

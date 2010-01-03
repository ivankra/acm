#include <iostream>
#include <algorithm>
using namespace std;

void pw(int a, int b, int x[]) {
	for (int i = 0; i < 1000; i++)
		x[i] = 0;
	x[0] = 1;
	for (int i = 0; i < b; i++)
		for (int j = 0, c = 0; j < 1000; j++, c /= 10)
			x[j] = (c += x[j] * a) % 10;
}

bool ls(int x[], int y[]) {
	for (int i = 999; i >= 0; i--)
		if (x[i] != y[i]) return x[i] < y[i];
	return false;
}

int main() {
	int a, b;
	cin >> a >> b;

	int x[1000], y[1000];
	pw(a, b, x);
	pw(b, a, y);

	if (ls(x, y)) {
		for (int i = 0; i < 1000; i++) swap(x[i], y[i]);
		cout << "-";
	}

	int c = 0;
	for (int i = 0; i < 1000; i++) {
		x[i] = x[i] - y[i] - c;
		if (x[i] < 0) { x[i] += 10; c = 1; } else { c = 0; }
	}

	int k;
	for (k = 999; k > 0 && x[k] == 0; k--);

	while (k >= 0) cout << (char)('0' + x[k--]);
	cout << endl;
}

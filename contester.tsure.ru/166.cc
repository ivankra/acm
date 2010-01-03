#include <iostream>
using namespace std;

int main()
{
	int day, month;
	cin >> day >> month;

	int len[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month < 1 || month > 12 || day < 1 || day > len[month]) {
		cout << "Impossible" << endl;
	} else {
		int w = 6;
		for (int d = 1, m = 1; d != day || m != month;) {
			w = (w + 1) % 7;
			if (++d > len[m]) {
				d = 1;
				m++;
			}
		}
		cout << w+1 << endl;
	}
}

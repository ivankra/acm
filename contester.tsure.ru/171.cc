#include <iostream>
#include <string>
#include <cctype>
using namespace std;

void up(string &s) {
	for (int i = 0; i < (int)s.size(); i++)
		s[i] = toupper(s[i]);
}

int main()
{
	string title, table[50][50];
	int w[50], n, m;

	cin >> title >> m;
	up(title);
	for (int i = 0; i < m; i++) {
		cin >> table[0][i];
		up(table[0][i]);
	}

	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < m; j++)
			cin >> table[i][j];

	int width = 1;

	for (int j = 0; j < m; j++) {
		w[j] = 1;
		for (int i = 0; i <= n; i++)
			w[j] = max(w[j], (int)(2+table[i][j].size()));
		width += w[j] + 1;
	}

	if (title.size()+4 > width) {
		w[m-1] += title.size()+4 - width;
		width = title.size() + 4;
	}

	cout << "+" << string(width-2, '-') << "+" << endl;
	cout << "|." << title << string(width-4-title.size(), '.') << ".|" << endl;

	for (int row = 0;; row++) {
		cout << "+";
		for (int col = 0; col < m; col++)
			cout << string(w[col], '-') << "+";
		cout << endl;

		if (row > n) break;

		cout << "|";
		for (int col = 0; col < m; col++)
			cout << "." << table[row][col] << string(w[col]-1-table[row][col].size(), '.') << "|";
		cout << endl;
	}
}

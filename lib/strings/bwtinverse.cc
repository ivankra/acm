// Burrows-Wheeler inverse transform.
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

string bwtInverse(const string &s, int r) {
	int cnt[256], n = s.size();
	for (int i = 0; i < 256; i++) cnt[i] = 0;
	for (int i = 0; i < n; i++) cnt[int(s[i])]++;
	for (int i = 1; i < 256; i++) cnt[i] += cnt[i-1];

	int *next = new int[n];
	for (int i = n-1; i >= 0; i--) next[--cnt[int(s[i])]] = i;

	string t;
	t.reserve(n);
	for (int i = r, k = 0; k < n; k++, i = next[i])
		t += s[i];
	delete[] next;

	return t;
}

int main(int argc, char *argv[])
{
	string s;
	int c;
	if (argc != 2) {
		fprintf(stderr, "Specify row number in command line\n");
		return 1;
	}
	while ((c = getchar()) != EOF) s += (char)c;
	s = bwtInverse(s, atoi(argv[1]));
	for (int i = 0; i < (int)s.size(); i++) putchar(s[i]);
	return 0;
}

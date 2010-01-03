#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

typedef vector<int> VI;

int score[32];

int teamByName(char c) { return isupper(c) ? (c - 'A') : (c - 'a' + 26); }
char teamName(int n) { return (n < 26) ? (n + 'A') : (n - 26 + 'a'); }

bool byScore1(int i, int j) { return (score[i] != score[j]) ? (score[i] > score[j]) : (i < j); }
bool byScore2(int i, int j) { return (score[i] != score[j]) ? (score[i] < score[j]) : (i < j); }

string rec(VI a) {
	int N = a.size();
	if (N == 2) {
		string s(2, ' ');
		s[0] = teamName(a[0]);
		s[1] = teamName(a[1]);
		if (s[0] > s[1]) swap(s[0], s[1]);
		return s;
	}

	int H = N/2;

	sort(a.begin(), a.end(), byScore1);
	string A = rec(VI(a.begin(), a.begin()+H));
	A += rec(VI(a.begin()+H, a.end()));

	sort(a.begin(), a.end(), byScore2);
	string B = rec(VI(a.begin(), a.begin()+H));
	B += rec(VI(a.begin()+H, a.end()));

	return min(A, B);
}

string rec(VI a, int our) {
	int N = a.size() + 1;
	if (N == 2) {
		string s(2, ' ');
		s[0] = teamName(a[0]);
		s[1] = teamName(our);
		if (s[0] > s[1]) swap(s[0], s[1]);
		return s;
	}

	int H = N/2;

	sort(a.begin(), a.end(), byScore1);
	string A = rec(VI(a.begin(), a.begin()+H));
	A += rec(VI(a.begin()+H, a.end()), our);

	sort(a.begin(), a.end(), byScore2);
	string B = rec(VI(a.begin(), a.begin()+(H-1)), our);
	B += rec(VI(a.begin()+(H-1), a.end()));

	return min(A, B);
}

int main() {
	int T, N, R;
	scanf("%d", &T);

	char our_c;
	for (int cs = 1; cs <= T && scanf("%d %c", &R, &our_c) == 2; cs++) {
		N = 1 << R;
		int our = teamByName(our_c);
		for (int i = 0; i < N; i++)
			scanf("%d", &score[i]);

		vector<int> avail;
		for (int i = 0; i < N; i++)
			if (i != our) avail.push_back(i);

		string s = rec(avail, our);
		printf("%s\n", s.c_str());
	}
}

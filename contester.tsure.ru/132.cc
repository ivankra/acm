#include <cstdio>
#include <cctype>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, string> P;

int main()
{
	map<string, int> M;
	vector<P> V;

	for (string word="";;) {
		int c = getchar();
		if (c != EOF && isalpha(c)) {
			word += c;
		} else if (word.size() > 0) {
			if (M.count(word) == 0) {
				M[word] = V.size();
				V.push_back(P(-1, word));
			} else {
				V[M[word]].first--;
			}
			word = "";
		}
		if (c == EOF) break;
	}

	sort(V.begin(), V.end());
	for (int i = 0; i < (int)V.size(); i++)
		printf("%s %d\n", V[i].second.c_str(), -V[i].first);
}

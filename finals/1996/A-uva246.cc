#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <vector>
#include <algorithm>
#include <deque>
#include <iostream>
#include <set>
#include <map>
using namespace std;
#define FOREACH(it,v) for(__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

set<string> seen;
deque<char> deck;
deque<deque<char> *> piles;

string encode()
{
	string res = "";
	FOREACH(it, deck) res += 'a'+(char)*it;
	FOREACH(p, piles) {
		res += ";";
		FOREACH(it, **p) res += 'a'+(char)*it;
	}
	return res;
}

int main()
{
	while (true) {
		deck.clear();
		seen.clear();
		for (int i = 0; i < 52; i++) {
			int x;
			if (scanf("%d", &x) != 1) return 0;
			if (x == 0) return 0;
			deck.push_back(x);
		}

		piles.clear();
		for (int i = 0; i < 7; i++) {
			piles.push_back(new deque<char>());
			piles.back()->push_back(deck.front());
			deck.pop_front();
		}

		int res = 7;

		while (true) {
			if (piles.size() == 0) {
				printf("Win : %d\n", res);
				break;
			}

			if (deck.size() == 0) {
				printf("Loss: %d\n", res);
				break;
			}

			string s = encode();
			if (seen.count(s) != 0) {
				printf("Draw: %d\n", res);
				break;
			}
			seen.insert(s);

			piles.push_back(piles.front());
			piles.pop_front();

			piles.back()->push_back(deck.front());
			deck.pop_front();
			res++;

			deque<char> &P = *piles.back();
			while (P.size() >= 3) {
				int n = P.size();

				if ((P[0] + P[1] + P.back()) % 10 == 0) {
					deck.push_back(P[0]);
					deck.push_back(P[1]);
					deck.push_back(P.back());
					P.pop_front();
					P.pop_front();
					P.pop_back();
					continue;
				}

				if ((P[0] + P[n-2] + P[n-1]) % 10 == 0) {
					deck.push_back(P[0]);
					deck.push_back(P[n-2]);
					deck.push_back(P[n-1]);
					P.pop_front();
					P.pop_back();
					P.pop_back();
					continue;
				}

				if ((P[n-3] + P[n-2] + P[n-1]) % 10 == 0) {
					deck.push_back(P[n-3]);
					deck.push_back(P[n-2]);
					deck.push_back(P[n-1]);
					P.pop_back();
					P.pop_back();
					P.pop_back();
					continue;
				}

				break;
			}

			if (P.size() == 0) {
				delete piles.back();
				piles.pop_back();
			}
		}
	}
}

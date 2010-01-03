#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Card {
	int face, suit;
	int face_c;

	bool read() {
		char s[16];
		if (scanf(" %[A-Z0-9]", s) != 1 || s[0] == '#') return false;

		face_c = s[0];
		suit = s[1];

		for (int i = 0; i < 13; i++)
			if (face_c == "23456789TJQKA"[i]) { face = i+2; break; }

		return true;
	}
};

struct Card trump, lead;
vector<Card> desk;

struct Player {
	vector<Card> hand;
	int score;

	void er(int k) {
		for (int i = k+1; i < (int)hand.size(); i++)
			hand[i-1] = hand[i];
		hand.pop_back();
	}

	void do_lead() {
		int high = hand[0].face;
		for (int i = 0; i < (int)hand.size(); i++)
			high = max(high, hand[i].face);

		int w = -1;
		for (int i = 0; i < (int)hand.size(); i++) {
			if (hand[i].face != high) continue;
			if (w < 0)
				w = i;
			else if (hand[i].suit == trump.suit)
				w = i;
			else if (hand[w].suit != trump.suit &&
				 hand[i].suit > hand[w].suit)
				w = i;
		}

		desk.push_back(hand[w]);
		lead = hand[w];
		er(w);
	}

	void do_follow() {
		int high = hand[0].face;
		for (int i = 0; i < (int)hand.size(); i++)
			high = max(high, hand[i].face);

		int w = -1;
		for (int i = 0; i < (int)hand.size(); i++) {
			if (hand[i].suit == lead.suit &&
			    (w < 0 || hand[i].face > hand[w].face))
				w = i;
		}
		if (w >= 0) goto done;

		for (int i = 0; i < (int)hand.size(); i++) {
			if (hand[i].suit == trump.suit &&
			    (w < 0 || hand[i].face > hand[w].face))
				w = i;
		}
		if (w >= 0) goto done;

		w = -1;
		for (int i = 0; i < (int)hand.size(); i++) {
			if (hand[i].face != high) continue;
			if (w < 0 || hand[i].suit > hand[w].suit)
				w = i;
		}

done:		desk.push_back(hand[w]);
		er(w);
	}
} player[5];

int main() {
	for (;;) {
		for (int i = 0; i < 5; i++) {
			player[i].hand.clear();
			player[i].score = 0;
		}

		for (int i = 0; i < 50; i++) {
			Card c;
			if (!c.read()) return 0;
			player[(1+i)%5].hand.push_back(c);
		}

		Card c1, c2;
		c1.read(); c2.read();

		if (c1.face != c2.face)
			trump = (c1.face > c2.face) ? c1 : c2;
		else
			trump = (c1.suit > c2.suit) ? c1 : c2;

		for (int T = 0, w = 1; T < 10; T++) {
			int who[5];

			desk.clear();
			player[w].do_lead();
			who[0] = w;
			for (int i = 1; i < 5; i++) {
				player[(w+i)%5].do_follow();
				who[i] = (w+i)%5;
			}

			int tr = lead.suit;
			for (int i = 0; i < 5; i++)
				if (desk[i].suit == trump.suit) tr = trump.suit;

			for (int i = 0; i < 5; i++)
				if (desk[i].suit == tr &&
				    (desk[w].suit != tr || desk[i].face > desk[w].face))
					w = i;
			w = who[w];

			for (int i = 0; i < 5; i++)
				if (desk[i].suit == 'H')
					player[w].score += desk[i].face;
		}

		for (int i = 0; i < 5; i++)
			printf(i<4?"%3d":"%3d\n", player[i].score);
	}
}

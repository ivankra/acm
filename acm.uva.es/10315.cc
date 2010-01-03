#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> VI;

int suit(int x) { return x >> 8; }
int value(int x) { return x & 0xff; }

int type(VI a, int *rank) {
	int of_value[16], nvalues=0, highest=value(a[0]), lowest=highest;
	memset(of_value, 0, sizeof(of_value));
	for (int i = 0; i < 5; i++) {
		int v = value(a[i]);
		highest >?= v;
		lowest <?= v;
		if (of_value[v]++ == 0) nvalues++;
	}

	int of_suit[4]={0,0,0,0}, nsuits=0;
	for (int i = 0; i < 5; i++)
		if (of_suit[suit(a[i])]++ == 0) nsuits++;

	*rank = 0;
	for (int i = 12; i >= 0; i--)
		for (int j = 0; j < of_value[i] && j < 1; j++)
			(*rank) = ((*rank) << 4) + i;

	// High Card: Hands which do not fit any higher category are ranked
	// by the value of their highest card. If the highest cards have the
	// same value, the hands are ranked by the next highest, and so on.
	*rank = 0;
	for (int i = 12; i >= 0; i--) {
		for (int j = 0; j < of_value[i] && j < 1; j++)
			(*rank) = ((*rank) << 4) | i;
	}

	// Straight flush: 5 cards of the same suit with consecutive values.
	// Ranked by the highest card in the hand.
	if (nsuits == 1 && nvalues == 5 && lowest+4==highest) {
		*rank = highest;
		return 8;
	}

	// Four of a kind: 4 cards with the same value. Ranked by the value of
	// the 4 cards.
	for (int i = 0; i < 13; i++) {
		if (of_value[i] == 4) {
			*rank = i;
			return 7;
		}
	}

	// Full House: 3 cards of the same value, with the remaining 2 cards
	// forming a pair. Ranked by the value of the 3 cards.
	for (int i = 0; i < 13; i++)
	for (int j = 0; j < 13; j++) {
		if (of_value[i] == 3 && of_value[j] == 2) {
			*rank = i;
			return 6;
		}
	}

	// Flush: Hand contains 5 cards of the same suit. Hands which are both
	// flushes are ranked using the rules for High Card.
	if (nsuits == 1)
		return 5;

	// Straight: Hand contains 5 cards with consecutive values. Hands which
	// both contain a straight are ranked by their highest card.
	if (nvalues == 5 && lowest+4==highest) {
		*rank = highest;
		return 4;
	}

	// Three of a Kind: Three of the cards in the hand have the same value.
	// Hands which both contain three of a kind are ranked by the value of
	// the 3 cards.
	for (int i = 0; i < 13; i++) {
		if (of_value[i] == 3) {
			*rank = i;
			return 3;
		}
	}

	// Two Pairs: The hand contains 2 different pairs. Hands which both
	// contain 2 pairs are ranked by the value of their highest pair.
	// Hands with the same highest pair are ranked by the value of their
	// other pair. If these values are the same the hands are ranked by
	// the value of the remaining card.
	for (int i = 0; i < 13; i++)
	for (int j = i+1; j < 13; j++) {
		if (of_value[i] == 2 && of_value[j] == 2) {
			for (int k = 0; k < 13; k++) {
				if (of_value[k] != 1) continue;
                                *rank = (j << 8) + (j << 4) + k;
				return 2;
			}
		}
	}

	// Pair: 2 of the 5 cards in the hand have the same value. Hands which
	// both contain a pair are ranked by the value of the cards forming the
	// pair. If these values are the same, the hands are ranked by the
	// values of the cards not forming the pair, in decreasing order.
	for (int i = 0; i < 13; i++) {
		if (of_value[i] == 2) {
			int z = i;
			of_value[i] = 0;
			for (int j = 12; j >= 0; j--)
				while (of_value[j]-- > 0) z = (z << 4) | j;
			*rank = z;
			return 1;
		}
	}

	// High Card rank
	return 0;
}

int get() {
	char *S="CDHS", *F="23456789TJQKA";
	int c, d;
	while ((c = getchar()) != EOF && !isalnum(c));
	if (c == EOF) return -1;
	while ((d = getchar()) != EOF && !isalnum(d));
	if (d == EOF) return -1;
	c = strchr(F, c) - F;
	d = strchr(S, d) - S;
	return c | (d << 8);
}

int main()
{
	for (;;) {
		VI h[2];
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < 5; i++) {
				int c = get();
				if (c < 0) return 0;
				h[k].push_back(c);
			}
		}

		int ar, at = type(h[0], &ar);
		int br, bt = type(h[1], &br);

		if (at > bt || (at == bt && ar > br))
			printf("Black wins.\n");
		else if (at == bt && ar == br)
			printf("Tie.\n");
		else
			printf("White wins.\n");
	}
	return 0;
}

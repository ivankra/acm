#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int bitcnt(int n) {
	int r = 0;
	while (n > 0) { r++; n &= n - 1; }
	return r;
}

struct KthElement {
	int find(int A, int B, int K) {
#define F(x) (A*bitcnt(x)+B)
		int p = 0, x = 0, y = 0;	/* x=y=initial element of sequence */
		do {
			if (K == 0) return x;
			p++; K--;
			x = F(x);
			y = F(y); y = F(y);
		} while (x != y);

		K %= p;
		while (K-- > 0) x = F(x);

		return x;
	}
};

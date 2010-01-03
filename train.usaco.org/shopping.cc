/*
ID: infnty1
PROB: shopping
LANG: C++
*/
#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

struct Offer {
	int orig_n, k[5], orig_c[5], orig_k[5], price;
};

vector<Offer> offers;
int regular[5];

struct Request {
	int n, k[5];
	bool operator <(const Request &z) const {
		if (n != z.n) return n < z.n;
		return memcmp(k, z.k, n*sizeof(int)) < 0;
	}
};

int memo[6*6*6*6*6+10];

int eval(Request rq) {
	int id = 0;
	for (int i = 0; i < rq.n; i++)
		id = id * 6 + rq.k[i];

	int &ret = memo[id];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < rq.n; i++)
		ret += regular[i] * rq.k[i];

	for (int off_id = 0; off_id < (int)offers.size(); off_id++) {
		Offer &o = offers[off_id];
		Request q = rq;

		bool ok = false;
		for (int i = 0; i < rq.n; i++) {
			if (q.k[i] < o.k[i]) goto skip;
			if (o.k[i] == 0) continue;
			q.k[i] -= o.k[i];
			ok = true;
		}

		if (ok)
			ret = min(ret, o.price + eval(q));
skip:;
	}

	return ret;
}

int main()
{
	freopen("shopping.in", "r", stdin);
	freopen("shopping.out", "w", stdout);

	int ns;
	scanf("%d", &ns);

	for (int i = 0; i < ns; i++) {
		Offer o;
		scanf("%d", &o.orig_n);
		for (int j = 0; j < o.orig_n; j++)
			scanf("%d %d", &o.orig_c[j], &o.orig_k[j]);
		scanf("%d", &o.price);
		offers.push_back(o);
	}

	int rc[10];
	Request r;
	map<int, int> c2i;

	scanf("%d", &r.n);
	for (int i = 0; i < r.n; i++) {
		scanf("%d %d %d", &rc[i], &r.k[i], &regular[i]);
		c2i[rc[i]] = i;
	}

	for (int i = 0; i < (int)offers.size(); i++) {
		Offer &o = offers[i];
		for (int j = 0; j < 5; j++)
			o.k[j] = 0;

		for (int j = 0; j < o.orig_n; j++) {
			if (c2i.count(o.orig_c[j]) == 0) goto rm;
			o.k[c2i[o.orig_c[j]]] = o.orig_k[j];
		}

		continue;

rm:		offers.erase(offers.begin() + i);
		i--;
	}

	memset(memo, 0xff, sizeof(memo));
	printf("%d\n", eval(r));

	return 0;
}

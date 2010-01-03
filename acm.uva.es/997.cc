#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
typedef vector<long long> VLL;

struct Node {
	char kind;
	long long m;
	Node *S;

	vector<long long> gen(int N) {
		if (kind == ']') {
			return vector<long long>(N, m);
		} else if (kind == '+') {
			VLL v = S->gen(N-1);
			VLL res(N);
			res[0] = m;
			for (int i = 1; i < N; i++)
				res[i] = res[i-1] + v[i-1];
			return res;
		} else {
			VLL v = S->gen(N);
			v[0] *= m;
			for (int i = 1; i < N; i++)
				v[i] *= v[i-1];
			return v;
		}
	}
};

Node *read() {
	Node *res = new Node();
	while (true) {
		if (scanf(" [ %lld %c", &res->m, &res->kind) != 2) exit(0);
		if (res->kind != ']') {
			res->S = read();
			scanf(" ] ");
		}
		return res;
	}
}

int main()
{
	int N;
	while (true) {
		Node *node = read();
		scanf("%d", &N);
		vector<long long> v = node->gen(N);
		for (int i = 0; i < N; i++)
			printf(i==0 ? "%lld" : " %lld", v[i]);
		printf("\n");
	}
}

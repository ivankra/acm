#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

// Representation of tree using first-child, next-sibling form.
// Vertices are numbered 0, 1, ..., N-1.
struct Tree {
	int N;
	int root;
	vector<int> firstChild, nextSibling;

	// Constructs the tree from a list of parents for each node.
	// parent[i] must contain the index of parent of i-th node, or -1 if i is root.
	static Tree fromParentsList(vector<int> parent) {
		Tree tree(parent.size());
		for (int x = 0; x < tree.N; x++) {
			int p = parent[x];
			if (p == -1) {
				tree.root = x;
			} else {
				tree.nextSibling[x] = tree.firstChild[p];
				tree.firstChild[p] = x;
			}
		}
		return tree;
	}

private:
	explicit Tree(int n) : N(n), root(0), firstChild(n, -1), nextSibling(n, -1) {}
};

// Offline LCA solver abstract base class
class OfflineLCASolver {
protected:
	const Tree &tree;
public:
	OfflineLCASolver(const Tree &tree_) : tree(tree_) {}
	virtual ~OfflineLCASolver() {}
	virtual vector<int> solve(const vector<pair<int, int> > &queries) = 0;
};

// Tarjan's offline LCA algorithm
class TarjansLCA : public OfflineLCASolver {
	// Union-Find data structure with path compression and union by rank
	struct UnionFind {
		vector<int> p, rank;

		UnionFind(int N = 1) {
			rank.assign(N, 0);
			p.resize(N);
			for (int i = 0; i < N; i++) p[i] = i;
		}

		int find(int x) {
			int y = p[x];
			while (p[y] != y) y = p[y];
			while (p[x] != y) {
				int z = p[x];
				p[x] = y;
				x = z;
			}
			return y;
		}

		void merge(int x, int y) {
			x = find(x);
			y = find(y);
			if (x != y) {
				if (rank[x] < rank[y]) {
					p[x] = y;
				} else if (rank[y] < rank[x]) {
					p[y] = x;
				} else {
					p[x] = y;
					rank[y]++;
				}
			}
		}
	};

	typedef pair<int, int> Pair;
	vector<int> answer;
	vector<vector<Pair> > queryList;
	vector<bool> visited;
	vector<int> ancestor;
	UnionFind uf;

	void dfs(int x) {
		ancestor[uf.find(x)] = x;
		for (int y = tree.firstChild[x]; y != -1; y = tree.nextSibling[y]) {
			dfs(y);
			uf.merge(x, y);
			ancestor[uf.find(x)] = x;
		}

		visited[x] = true;

		vector<Pair>::const_iterator it = queryList[x].begin();
		for (; it != queryList[x].end(); ++it) {
			if (visited[it->first])
				answer[it->second] = ancestor[uf.find(it->first)];
		}
	}

public:
	TarjansLCA(const Tree &tree_) : OfflineLCASolver(tree_) {}

	virtual vector<int> solve(const vector<pair<int, int> > &Q) {
		answer.assign(Q.size(), -1);
		queryList.assign(tree.N, vector<Pair>());
		for (int i = 0; i < (int)Q.size(); i++) {
			int x = Q[i].first;
			int y = Q[i].second;
			queryList[x].push_back(Pair(y, i));
			queryList[y].push_back(Pair(x, i));
		}
		uf = UnionFind(tree.N);
		visited.assign(tree.N, false);
		ancestor.assign(tree.N, -1);
		dfs(tree.root);
		queryList.clear();
		return answer;
	}
};

// Trivial solver
class TrivialLCA : public OfflineLCASolver {
	typedef pair<int, int> Pair;
	vector<int> depth, parent;

	void dfs(int x) {
		for (int y = tree.firstChild[x]; y != -1; y = tree.nextSibling[y]) {
			parent[y] = x;
			depth[y] = depth[x] + 1;
			dfs(y);
		}
	}

public:
	TrivialLCA(const Tree &tree_) : OfflineLCASolver(tree_) {
		depth.assign(tree.N, 0);
		parent.assign(tree.N, -1);
		dfs(tree.root);
	}

	virtual vector<int> solve(const vector<pair<int, int> > &Q) {
		vector<int> answer;
		for (int i = 0; i < (int)Q.size(); i++) {
			int x = Q[i].first;
			int y = Q[i].second;

			while (x != y) {
				if (depth[x] > depth[y])
					x = parent[x];
				else
					y = parent[y];
			}

			answer.push_back(x);
		}
		return answer;
	}
};


int main()
{
	srand(19562921);
	for (int cs = 1; cs <= 10; cs++) {
		int N = 10 + rand() % 1000;

		vector<int> parent(N);
		parent[0] = -1;
		for (int x = 1; x < N; x++)
			parent[x] = rand() % x;

		Tree tree = Tree::fromParentsList(parent);

		vector<pair<int, int> > Q;
		for (int x = 0; x < N; x++)
			for (int y = 0; y < N; y++)
				Q.push_back(pair<int, int>(x, y));

		TarjansLCA solver1(tree);
		TrivialLCA solver2(tree);

		vector<int> answer1 = solver1.solve(Q);
		vector<int> answer2 = solver2.solve(Q);

		if (answer1 == answer2)
			;
		else {
			assert(answer1.size() == Q.size());
			assert(answer2.size() == Q.size());
			for (int i = 0; i < (int)Q.size(); i++) {
				if (answer1[i] != answer2[i]) {
					printf("x=%d y=%d: tarjan's=%d actual=%d\n",
						Q[i].first, Q[i].second,
						answer1[i], answer2[i]);
				}
			}
		}

		assert(answer1 == answer2);

		printf("Test %d (N=%d) OK\n", cs, N);
	}
}

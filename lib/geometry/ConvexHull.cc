// Implementation of Monotone Chain 2D Convex Hull algorithm.
//
// References:
// * De Berg, van Kreveld, Overmars, Schwarzkopf. Computational Geometry:
//   Algorithms and Applications. 2nd edition, Springer-Verlag. ISBN 3540656200.
// * http://geometryalgorithms.com/Archive/algorithm_0109/algorithm_0109.htm
//
// Asymptotic complexity: O(n log n)
// Practical performance: 0.5-1.0 seconds for n=1000000 on a 1GHz machine
//
#include <algorithm>
#include <vector>
using namespace std;

struct Point {
	long long x, y;

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

// 2D cross product.
// Return a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
long long cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convexHull(vector<Point> P)
{
	int n = P.size(), k = 0;
	vector<Point> H(2*n);

	// Sort points lexicographically
	sort(P.begin(), P.end());

	// Build lower hull
	for (int i = 0; i < n; i++) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	H.resize(k);
	return H;
}

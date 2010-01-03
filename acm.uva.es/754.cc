#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
using namespace std;

template<typename T> int size(const T &container) { return container.size(); }

const double EPS = 1e-6;

struct Point {
	double x, y;
	Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};

double cross(const Point &o, const Point &a, const Point &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

struct Line {
	double a, b, c;
	Line() {}
	Line(const Point &A, const Point &B) {
		a = B.y - A.y;
		b = A.x - B.x;
		c = a * A.x + b * A.y;
	}
};

struct Vertex {
	Point point;
	int wall[2];
	vector<int> adj;	// adjacent vertices
};

struct Wall {
	Line line;
	vector<int> vert;
	Wall(Point A, Point B) : line(A, B) {}
};

vector<Vertex> Vertices;

struct Room {
	vector<int> vert;	// list of vertices in ccw order
	vector<int> adj;	// adjacent rooms

	bool isInside(const Point &q) const {
		int n = size(vert);
		for (int i = 0; i < n; i++) {
			const Point &a = Vertices[vert[i]].point;
			const Point &b = Vertices[vert[(i+1)%n]].point;
			if (cross(a, b, q) < EPS) return false;
		}
		return true;
	}
};

typedef pair<int, int> Edge;

vector<Wall> Walls;
vector<Room> Rooms;
map<Edge, int> EdgeMap;     // maps oriented edges to room ids.
Point treasury;

bool vertexSort(int i, int j) {
	const Point &a = Vertices[i].point;
	const Point &b = Vertices[j].point;
	return a.x < b.x - EPS || (a.x < b.x + EPS && a.y < b.y);
}

int solveCase()
{
	Vertices.clear();
	EdgeMap.clear();
	Rooms.clear();

	// Generate vertices
	for (int i = 0; i < size(Walls); i++) {
		for (int j = i+1; j < size(Walls); j++) {
			Line l = Walls[i].line;
			Line m = Walls[j].line;
			double det = l.a * m.b - l.b * m.a;
			if (fabs(det) < EPS) continue;

			Vertex v;
			v.point.x = (l.c * m.b - l.b * m.c) / det;
			v.point.y = (l.a * m.c - l.c * m.a) / det;
			if (v.point.x < -EPS || v.point.x > 100+EPS) continue;
			if (v.point.y < -EPS || v.point.y > 100+EPS) continue;

			v.wall[0] = i;
			v.wall[1] = j;
			int id = Vertices.size();
			Vertices.push_back(v);
			Walls[i].vert.push_back(id);
			Walls[j].vert.push_back(id);
		}
	}

	// Sort vertices on each wall in lexicographic order, so that
	// adjacent vertices come together.
	for (int i = 0; i < size(Walls); i++) {
		vector<int> &v = Walls[i].vert;
		sort(v.begin(), v.end(), vertexSort);

		// link adjacent vertices
		for (int j = 1; j < size(v); j++) {
			Vertex &a = Vertices[v[j-1]];
			Vertex &b = Vertices[v[j]];
			a.adj.push_back(v[j]);
			b.adj.push_back(v[j-1]);
		}
	}

	// Discover rooms
	for (int s = 0; s < size(Vertices); s++) {
		for (int si = 0; si < size(Vertices[s].adj); si++) {
			int a = s;
			int b = Vertices[a].adj[si];

			Edge e(a, b);
			if (EdgeMap.count(e) != 0) continue;

			Room room;
			int room_id = size(Rooms);
			room.vert.push_back(a);
			room.vert.push_back(b);
			EdgeMap[Edge(a, b)] = room_id;

			/*printf("room: (%.1f, %.1f) - (%.1f, %.1f)",
				Vertices[a].point.x, Vertices[a].point.y,
				Vertices[b].point.x, Vertices[b].point.y);*/

			for (;;) {
				int c = -1;
				for (int i = 0; i < size(Vertices[b].adj); i++) {
					int d = Vertices[b].adj[i];
					if (d == a) continue;

					if (size(Vertices[b].adj) != 2) {
						if (cross(Vertices[a].point, Vertices[b].point, Vertices[d].point) < -EPS)
							continue;
					}

					if (c < 0 || cross(Vertices[b].point, Vertices[c].point, Vertices[d].point) > 0) {
						c = d;
					}
				}

				assert(c != -1);
				//printf(" - (%.1f, %.1f)\n", Vertices[c].point.x, Vertices[c].point.y);
				assert(EdgeMap.count(Edge(b, c)) == 0);

				EdgeMap[Edge(b, c)] = room_id;
				if (c == s) break;
				room.vert.push_back(c);
				a = b;
				b = c;
			}

			//printf("\n");

			Rooms.push_back(room);
		}
	}

	// Find adjacent rooms
	for (int i = 0; i < size(Rooms); i++) {
		Room &room = Rooms[i];
		room.adj.clear();
		for (int j = 0; j < size(room.vert); j++) {
			int a = room.vert[j];
			int b = room.vert[(j + 1) % size(room.vert)];
			assert(EdgeMap.count(Edge(b, a)) != 0);
			int r = EdgeMap[Edge(b, a)];
			assert(r != i);
			room.adj.push_back(r);
		}
	}

	int externalRoom = 0;
	int treasureRoom = -1;

	// find treasure room
	for (int i = 0; i < size(Rooms); i++) {
		if (Rooms[i].isInside(treasury)) {
			treasureRoom = i;
			break;
		}
	}
	assert(treasureRoom != -1);

	// Finally, BFS

	vector<int> dist(size(Rooms), 1000000);
	dist[externalRoom] = 0;

	queue<int> Q;
	Q.push(externalRoom);

	while (!Q.empty()) {
		int r = Q.front();
		Q.pop();

		if (r == treasureRoom)
			return dist[r];

		for (int i = 0; i < size(Rooms[r].adj); i++) {
			int s = Rooms[r].adj[i];
			if (dist[s] > dist[r] + 1) {
				dist[s] = dist[r] + 1;
				Q.push(s);
			}
		}
	}

	abort();
	return 42;
}

int main()
{
	int T, K;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &K);

		Walls.clear();
		Walls.push_back(Wall(Point(0, 100), Point(0, 0)));
		Walls.push_back(Wall(Point(0, 0), Point(100, 0)));
		Walls.push_back(Wall(Point(100, 0), Point(100, 100)));
		Walls.push_back(Wall(Point(100, 100), Point(0, 100)));

		for (int id = 1; id <= K; id++) {
			Point A, B;
			scanf("%lf %lf %lf %lf", &A.x, &A.y, &B.x, &B.y);
			Walls.push_back(Wall(A, B));
		}

		scanf(" %lf %lf", &treasury.x, &treasury.y);

		int res = solveCase();

		printf("Number of doors = %d\n", res);
		if (cs != T) printf("\n");
	}
}

#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <algorithm>
#include <deque>
#include <iostream>
#include <set>
using namespace std;

int nrooms, nbeds, npatients, startTime;
int transportTime, roomCleanTime, bedCleanTime;

struct Patient {
	int id, time1, time2;
	char name[20];
	int room, bed, roomStart;
} patients[1000];

struct Facility {
	int avail;
	int used;
	int cur;
} rooms[50], beds[50];

enum { BED_READY=1, ROOM_READY=2, LEAVE_BED=3, LEAVE_ROOM=4 };

struct Event {
	int t, kind, x;

	Event(int t_, int kind_, int x_) : t(t_), kind(kind_), x(x_) {}

	bool operator <(const Event &e) const {
		if (t != e.t) return t < e.t;
		if (kind != e.kind) return kind < e.kind;
		return x < e.x;
	}
};

int nextPatient, curTime, endTime, freeRooms;
set<Event> events;

void simulate()
{
	for (int i = 0; i < nrooms; i++) { rooms[i].avail = 1; rooms[i].used = 0; }
	freeRooms = nrooms;
	for (int i = 0; i < nbeds; i++) { beds[i].avail = 1; beds[i].used = 0; }

	nextPatient = 0;
	events.clear();
	curTime = startTime;
	endTime = startTime;

	while (events.size() != 0 || nextPatient < npatients) {
		if (events.size() != 0 && events.begin()->t == curTime) {
			Event e = *events.begin();
			events.erase(events.begin());

			if (e.kind == LEAVE_ROOM) {
				int room = e.x;
				Patient &p = patients[rooms[room].cur];
				for (p.bed = 0; p.bed < nbeds && beds[p.bed].avail == 0; p.bed++);
				assert(p.bed < nbeds);
				beds[p.bed].avail = 0;

				rooms[p.room].used += p.time1;
				beds[p.bed].used += p.time2;

				events.insert(Event(curTime + roomCleanTime, ROOM_READY, p.room));
				events.insert(Event(curTime + transportTime + p.time2, LEAVE_BED, p.id));
			} else if (e.kind == ROOM_READY) {
				rooms[e.x].avail = 1;
				freeRooms++;
			} else if (e.kind == LEAVE_BED) {
				Patient &p = patients[e.x];
				endTime = max(endTime, curTime);
				events.insert(Event(curTime + bedCleanTime, BED_READY, p.bed));
			} else if (e.kind == BED_READY) {
				beds[e.x].avail = 1;
			}

			continue;
		}

		if (freeRooms != 0 && nextPatient < npatients) {
			Patient &p = patients[nextPatient++];
			for (p.room = 0; p.room < nrooms && rooms[p.room].avail == 0; p.room++);
			assert(p.room < nrooms);
			p.roomStart = curTime;
			rooms[p.room].avail = 0;
			rooms[p.room].cur = p.id;
			freeRooms--;
			events.insert(Event(curTime + p.time1, LEAVE_ROOM, p.room));
			continue;
		}

		assert(events.size() != 0);
		curTime = events.begin()->t;
	}


}

char *fmt(int minutes) {
	static char buf[100][100];
	static int z = 0;
	z = (z + 1) % 100;
	sprintf(buf[z], "%2d:%.2d", minutes / 60, minutes % 60);
	return buf[z];
}

int main()
{
	while (cin >> nrooms >> nbeds >> startTime >> transportTime >>
			roomCleanTime >> bedCleanTime >> npatients)
	{
		startTime *= 60;

		for (int i = 0; i < npatients; i++) {
			Patient &p = patients[i];
			p.id = i;
			cin >> p.name >> p.time1 >> p.time2;
		}

		simulate();

		printf(" Patient          Operating Room          Recovery Room\n");
		printf(" #  Name     Room#  Begin   End      Bed#  Begin    End\n");
		printf(" ------------------------------------------------------\n");
		for (int i = 0; i < npatients; i++) {
			Patient &p = patients[i];
			printf("%2d  %-8s %3d   %s   %s    %3d   %s   %s\n",
					i+1, p.name, p.room+1,
					fmt(p.roomStart), fmt(p.roomStart + p.time1),
					p.bed+1,
					fmt(p.roomStart + p.time1 + transportTime),
					fmt(p.roomStart + p.time1 + transportTime + p.time2));
		}
		printf("\n");
		printf("Facility Utilization\n");
		printf("Type  # Minutes  %% Used\n");
		printf("-------------------------\n");
		for (int i = 0; i < nrooms+nbeds; i++) {
			Facility &z = (i < nrooms ? rooms[i] : beds[i-nrooms]);
			long long num = z.used;
			long long den = endTime - startTime;
			if (den == 0 || num > den) { num = 1; den = 1; }
			int m = (num * 20000 + den) / (2 * den);
			printf("%s %2d %7d %4d.%.2d\n",
					(i < nrooms ? "Room" : "Bed "),
					(i < nrooms ? (i + 1) : (i - nrooms + 1)),
					z.used, m / 100, m % 100);
		}
		printf("\n");
	}
}

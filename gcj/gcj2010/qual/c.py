#!/usr/bin/env python
import sys

T = int(sys.stdin.readline())
for case in xrange(1, T + 1):
    max_rides, capacity, N = map(int, sys.stdin.readline().split())
    groups = map(int, sys.stdin.readline().split())

    def solve():
        res = 0
        head = 0
        rides = 0
        cache = dict()

        while rides < max_rides:
            if head in cache:
                d_rides = rides - cache[head][0]
                d_res = res - cache[head][1]
                if d_rides <= max_rides - rides:
                    k = (max_rides - rides) // d_rides
                    rides += d_rides * k
                    res += d_res * k
                    continue
            else:
                cache[head] = (rides, res)

            riders = 0
            init_head = head
            while riders + groups[head] <= capacity:
                riders += groups[head]
                head = (head + 1) % len(groups)
                if head == init_head:
                    break
            res += riders
            rides += 1

        return res

    print 'Case #%d: %d' % (case, solve())

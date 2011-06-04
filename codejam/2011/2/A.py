#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

def readline():
    return sys.stdin.readline()

def main():
    num_cases = int(readline())

    for cs in xrange(1, num_cases+1):
        X, S, R, T, N = map(int, readline().split())

        segments = []
        for i in xrange(N):
            B, E, W = map(int, readline().split())
            for each in xrange(E-B):
                segments.append(W + S)

        assert len(segments) <= X
        segments += [S] * (X - len(segments))

        delta = R - S
        segments.sort()

        res = 0

        i = 0
        while i < len(segments):
            fast_time = min(1, min(T, 1.0 / (segments[i] + delta)))
            fast_len = fast_time * (segments[i] + delta)
            slow_time = (1 - fast_len) / float(segments[i])

            res += fast_time + slow_time
            T -= fast_time

            i += 1

        print 'Case #%d: %.9g' % (cs, res)
        sys.stdout.flush()

if __name__ == '__main__':
    main()

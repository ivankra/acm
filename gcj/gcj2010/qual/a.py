#!/usr/bin/env python
import sys

T = int(sys.stdin.readline())
for case in xrange(1, T + 1):
    N, K = map(int, sys.stdin.readline().split())
    if ((K + 1) & ((1L << N) - 1)) == 0:
        print 'Case #%d: ON' % case
    else:
        print 'Case #%d: OFF' % case

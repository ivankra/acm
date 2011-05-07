#!/usr/bin/env python
import os, sys

T = int(sys.stdin.readline())
for cs in range(1, T+1):
    N, M = map(int, sys.stdin.readline().split())

    dirs = set()
    dirs.add('/')

    def create(path):
        path = path[1:].rstrip('/').split('/')
        dir = ''
        for name in path:
            dir += '/' + name
            dirs.add(dir)

    for each in range(N):
        dir = sys.stdin.readline().strip()
        create(dir)
    cnt1 = len(dirs)
    for each in range(M):
        dir = sys.stdin.readline().strip()
        create(dir)
    cnt2 = len(dirs)

    print 'Case #%d: %d' % (cs, cnt2 - cnt1)
    

#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

def solve(C, D, S):
    cur = ''

    for ch in S:
        cur += ch

        while True:
            replaced = 0
            for c in C:
                if cur.endswith(c[0] + c[1]) or cur.endswith(c[1] + c[0]):
                    cur = cur[:-2] + c[2]
                    replaced = 1
            if not replaced:
                break

        for d in D:
            if d[0] in cur and d[1] in cur:
                cur = ''
                break

    return '[' + ', '.join(cur) + ']'

def main():
    T = int(sys.stdin.readline())

    for cs in range(1, T+1):
        line = sys.stdin.readline().split()

        NC = int(line[0])
        C = line[1:NC+1]
        line = line[NC+1:]

        ND = int(line[0])
        D = line[1:ND+1]
        line = line[ND+1:]

        assert len(line) == 2 and len(line[1]) == int(line[0])
        S = line[1]

        print 'Case #%d: %s' % (cs, solve(C, D, S))


if __name__ == '__main__':
    main()

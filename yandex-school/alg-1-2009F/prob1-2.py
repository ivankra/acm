#!/usr/bin/env python
import sys

def solve(input):
    stack = []
    closing_of = { '(': ')', '[': ']', '{': '}' }

    for i, c in enumerate(input):
        if c in '([{':
            stack.append(c)
        elif len(stack) > 0 and c == closing_of[stack[-1]]:
            stack.pop()
        else:
            return i

    if len(stack) > 0:
        return len(input)
    return 'CORRECT'

print solve(sys.stdin.readline().strip())

#!/usr/bin/env python
import re
import sys
from pathlib import Path


pattern = re.compile(r'^#inc(lude|bin) "(?P<file>.+?)"', re.MULTILINE)
def scan(path):
    if not path.exists():
        return []
    with open(path) as file:
        content = file.read()
    return [
        (mode, path.parent / file)
        for mode, file in pattern.findall(content)
    ]
    

def main(argv=None):
    argv = argv or sys.argv[1:]
    if len(argv) < 1:
        print(f'usage: {sys.argv[0]} FILES...', file=sys.stderr)
        exit(1)
    A = [Path(x) for x in argv]
    W = [x for x in A]
    P = []
    while W:
        file, W = W[0], W[1:]
        t = scan(file)
        W += [x for mode, x in t if x not in P and mode != 'bin']
        P += [x for mode, x in t if x not in P]
    print('\n'.join([str(x) for x in P]))


if __name__ == "__main__":
    exit(main())

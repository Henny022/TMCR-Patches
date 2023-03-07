import re
import sys
from pathlib import Path


pattern = re.compile(r'#inc(lude|bin) "(?P<file>.+?)"')
def scan(path):
    if not path.exists():
        return []
    with open(path) as file:
        content = file.read()
    return [
        path.parent / file
        for mode, file in pattern.findall(content)
        if mode != 'bin'
    ]
    

def main(argv=None):
    argv = argv or sys.argv[1:]
    if len(argv) < 1:
        print(f'usage: {sys.argv[0]} FILES...', file=sys.stderr)
        exit(1)
    W = [Path(x) for x in argv]
    P = []
    while W:
        file, W = W[0], W[1:]
        P.append(file)
        t = scan(file)
        W += [x for x in t if x not in P]
    print('\n'.join([str(x) for x in P if x not in argv]))


if __name__ == "__main__":
    exit(main())

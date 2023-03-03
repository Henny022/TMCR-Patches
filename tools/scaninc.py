import re
import sys
import os.path


pattern = re.compile(r'#include "(?P<file>.+?)"')
def scan(filename):
    if not os.path.exists(filename):
        return []
    with open(filename) as file:
        content = file.read()
    return pattern.findall(content)
    

def main(argv=None):
    argv = argv or sys.argv[1:]
    if len(argv) < 1:
        print(f'usage: {sys.argv[0]} FILES...')
    W = [x for x in argv]
    P = []
    while W:
        file, W = W[0], W[1:]
        P.append(file)
        t = scan(file)
        W += [x for x in t if x not in P]
    print('\n'.join([x for x in P if x not in argv]))


if __name__ == "__main__":
    exit(main())

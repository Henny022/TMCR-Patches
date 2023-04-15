#!/usr/bin/env python

import json
from pathlib import Path


def dump_list(data, name, type):
    print('ALIGN 4')
    print(f'n_{name}:')
    print(f'WORD {len(data)}')
    print(f'{name}:')
    for entry in data:
        print(f'{type} {entry}')


def main():
    merged = {
        'flags': [],
        'fusions': [],
        'items': [],
    }
    for module in Path('modules').iterdir():
        with open(module) as module:
            module = json.load(module)
            for key in merged:
                if key in module:
                    merged[key] += module[key]
    dump_list(merged['flags'], 'starting_flags', 'SHORT')
    dump_list(merged['fusions'], 'starting_fusions', 'BYTE')
    dump_list(merged['items'], 'starting_items', 'BYTE')


if __name__ == '__main__':
    main()

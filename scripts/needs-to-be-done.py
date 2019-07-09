#!/usr/bin/env python3

import sys
import argparse

p = argparse.ArgumentParser("Retrieve all python info from given expr and add it to the NEEDS-TO-BE-DONE.md file")
p.add_argument('expr')
opts = p.parse_args()

ntbd = open('NEEDS-TO-BE-DONE.md').read().split('\n')

ntbd.append('[ ] {}'.format(opts.expr))
for x in dir(eval(opts.expr)):
    if x.startswith('_'):
        continue
    ntbd.append('[ ] {}.{}'.format(opts.expr, x))

with open('NEEDS-TO-BE-DONE.md', 'w') as f:
    content = list(set(ntbd))
    content.sort()
    f.write('\n'.join(filter(None, content)))

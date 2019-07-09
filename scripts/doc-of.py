#!/usr/bin/env python3

import sys
import argparse

p = argparse.ArgumentParser("Retrieve python doc from given expr")
p.add_argument('expr')
opts = p.parse_args()

sys.stdout.write('# {}\n'.format(opts.expr))
sys.stdout.write(eval(opts.expr).__doc__)
sys.stdout.write('\n- - -\n\n')
for x in dir(eval(opts.expr)):
    if x.startswith('_'):
        continue
    sys.stdout.write('## {}.{}\n'.format(opts.expr, x))
    sys.stdout.write(eval('{}.{}'.format(opts.expr, x)).__doc__)
    sys.stdout.write('\n- - -\n\n')

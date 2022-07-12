#!/usr/bin/python3

import sys
import random

if len(sys.argv) != 4:
	print ('Usage:	1st argument == numberOfRandomNumber.')
	print ('	2nd & 3rd argument == [start & end[ of interval')
	sys.exit(1)

try:
	tab = random.sample(range(int(sys.argv[2]), int(sys.argv[3])), int(sys.argv[1]))
except ValueError:
	print('Sample size exceeded population size.')
	sys.exit(1)
print(' '.join(map(str,tab)))
#! /usr/local/bin/python3

import random
import string

lens = [57, 56, 55, 54, 53, 52, 51, 50, 49]

for i in lens:
	with open("TimeBenchmarkFiles/" + str(i) + "len", "w") as f:
		f.write(''.join(random.choices(string.ascii_lowercase + string.ascii_uppercase + string.digits, k=i)))
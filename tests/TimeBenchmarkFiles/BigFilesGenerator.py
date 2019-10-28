#! /usr/local/bin/python3

import random
import string

lens = [52428800, 1073741824, 2147483648, 4294967296]

#for i in lens:
#	with open("TimeBenchmarkFiles/" + str(i) + "len", "w") as f:
#		f.write(''.join(random.choices(string.ascii_lowercase + string.ascii_uppercase + string.digits, k=i)))

for i in lens:
	with open("TimeBenchmarkFiles/" + str(i) + "len", "w") as f:
		f.write("abcd" * (i//4))

#! /usr/local/bin/python3

import random
import string

for i in range(1, 10):
	print(''.join(random.choices(string.ascii_lowercase + string.ascii_uppercase + string.digits, k=i)))


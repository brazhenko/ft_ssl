#! /usr/local/bin/python3

import random
import string

lens = range(0, 128, 1)

for i in lens:
    with open("testfiles/" + str(i) + "len", "w") as f:
        f.write(''.join(random.choices(string.ascii_lowercase + string.ascii_uppercase + string.digits, k=i)))
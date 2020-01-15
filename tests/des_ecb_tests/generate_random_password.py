#! /usr/local/bin/python3

import random
import string
KEY_LEN=random.randint(0, 25)

print(''.join(random.choices(string.ascii_lowercase + string.ascii_uppercase + string.digits, k=KEY_LEN)))
#print(''.join(random.choices(string.ascii_lowercase + string.ascii_uppercase + string.digits, k=KEY_LEN)))
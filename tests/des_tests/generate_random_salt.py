#! /usr/local/bin/python3

import random
import string
KEY_LEN=random.randint(1, 16)

key = ''.join(random.choices("1234567890ABCDEF", k=KEY_LEN))
print(key)
#print(''.join(random.choices(string.ascii_lowercase + string.ascii_uppercase + string.digits, k=KEY_LEN)))

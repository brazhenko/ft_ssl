# ft_ssl

ft_ssl is a C pet-project from 42 course written (tasks are available 
[here](ft_ssl_md5.en.pdf) and [here](ft_ssl_des.pdf)) in order to know more about
cryptography and security. Some standard, cipher and hashing OPENSSL's commands
are recoded here. Its output is compatible with OPENSSL's one.

## Installation

```bash
cmake . && make
```

## Usage

```bash

./ft_ssl command [command opts] [command args] 
./ft_ssl des-ecb -e -in file.txt -p MySuperSecurePassword
```

## Available commands

#### Hash commands
* md5
* sha256
#### Cipher commands
* des-ecb
#### Encoding commands
* base64
#### Standard commands

## Contributing

## License
[MIT](https://choosealicense.com/licenses/mit/)
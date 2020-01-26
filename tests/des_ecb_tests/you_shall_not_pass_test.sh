#!/bin/bash

bin="../../cmake-build-debug/ft_ssl"
# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}des_ecb encrypt file tests${NC}"
echo "$(curl 'https://www.peereboom.us/assl/assl/html/openssl.html')" > original.html
echo "password" > password_file
openssl des-ecb -p -in original.html -out ciphertext.html -pass "pass:$(cat password_file)"
./$bin des-ecb -d -i ciphertext.html -o decrypted.html -p "$(cat password_file)"
DIFF=$(diff original.html decrypted.html)
if [ "$DIFF" == "" ]
  then
      echo -e "${GREEN}Passed!${NC}"
else
      echo -e "${RED}Failed!${NC}"
fi
rm original.html ciphertext.html decrypted.html
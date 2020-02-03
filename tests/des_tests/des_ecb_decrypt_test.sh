#!/bin/bash

if [ "" == "$bin" ]
  then
    exit 0
fi

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

###############################################################################
# des_ecb key-decrypt file tests
###############################################################################
echo -e "${BLUE}des_ecb key-decrypt file tests${NC}"
for entry in "test_files"/*
do
  KEY=$(python3 generate_random_key.py)
  openssl des-ecb -K $KEY -in $entry | openssl  des-ecb -d  -K $KEY | base64 > orig
  openssl des-ecb -K $KEY -in $entry | ./$bin des-ecb -d -k $KEY | base64 > my

  echo -n -e  "$entry " "\t" "$KEY "
  DIFF=$(diff my orig)
  if [ "$DIFF" == "" ]
  then
      echo -e "${GREEN}Passed!${NC}"
  else
      echo -e "${RED}Failed!${NC}"
  fi
  rm my orig
done

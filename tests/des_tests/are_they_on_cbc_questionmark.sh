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

echo -e "${BLUE}des_cbc Are they on the Cipher BlockChain?${NC}"

PHRASE="Make sure they really tell you what is going on 'under the hood' then you use CBC mode, and how it is more secure than ECB"
KEY=BABE101010FACADE
IV=77696E6B66616365
ANSWER=$(echo $PHRASE | openssl des-cbc -K $KEY -iv $IV | $bin des-cbc -k $KEY -v $IV -d)

if [ "$ANSWER" == "$PHRASE" ]
  then
      echo -e "${GREEN}Passed!${NC}"
else
      echo -e "${RED}Failed!${NC}"
fi


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

echo -e "${BLUE}des_ecb easy tests${NC}"

export DES_KEY="C0FFEE69DEADBEEF"

VAR=$(echo "foo bar" | $bin des-ecb -k $DES_KEY | openssl des-ecb -d -K "$DES_KEY")
if [ "$VAR" == "foo bar" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

VAR=$(echo "foo bar" | openssl des-ecb -K "$DES_KEY" | $bin des-ecb -d -k $DES_KEY )
if [ "$VAR" == "foo bar" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi


VAR=$(echo "smol" | $bin des-ecb -k $DES_KEY | openssl des-ecb -d -K "$DES_KEY")
if [ "$VAR" == "smol" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

VAR=$(echo "smol" | openssl des-ecb -K "$DES_KEY" | $bin des-ecb -d -k $DES_KEY )
if [ "$VAR" == "smol" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

VAR=$(echo "testing the key now" | openssl des-ecb -K "ABCD" | $bin des-ecb -d -k "ABCD" )
if [ "$VAR" == "testing the key now" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi


VAR=$(echo "More key tests" | openssl des-ecb -K "FFFFFFFFFFFFFFFF" | $bin des-ecb -d -k "FFFFFFFFFFFFFFFF" )
if [ "$VAR" == "More key tests" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

VAR=$(echo "what kind of lock takes no key?" | openssl des-ecb -K "00000000" | $bin des-ecb -d -k "00000000")

if [ "$VAR" == "what kind of lock takes no key?" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

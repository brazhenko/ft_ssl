#!/bin/bash

bin="../../cmake-build-debug/ft_ssl"
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
  IV=$(python3 generate_random_key.py)
  openssl des-cbc -K $KEY -iv $IV -in $entry | openssl  des-cbc -d  -K $KEY -iv $IV | base64 > orig
  openssl des-cbc -K $KEY -iv $IV -in $entry | ./$bin des-cbc -d -k $KEY -v $IV | base64 > my
# openssl des-cbc -K DF183D226910 -iv  962F6D26E9DE  -in test_files/7len | ./$bin des-cbc -d -k DF183D226910 -v 962F6D26E9DE
  echo -n -e  "$entry " "\t" "$KEY " "\t" "$IV "
  DIFF=$(diff my orig)
  if [ "$DIFF" == "" ]
  then
      echo -e "${GREEN}Passed!${NC}"
  else
      echo -e "${RED}Failed!${NC}"
  fi
  rm my orig
done

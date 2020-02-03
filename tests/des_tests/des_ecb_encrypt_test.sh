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
# des_ecb key-encrypt file tests
###############################################################################
echo -e "${BLUE}des_ecb encrypt file tests${NC}"
for entry in "test_files"/*
do
  KEY=$(python3 generate_random_key.py)
  openssl des-ecb -K $KEY -in $entry | base64 > orig
  ./$bin des-ecb -i $entry -k $KEY | base64 > my

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

################################################################################
# des_ecb pass-encrypt file tests
################################################################################
#echo -e "${BLUE}des_ecb encrypt file tests${NC}"
#for entry in "test_files"/*
#do
#  KEY=$(python3 generate_random_key.py)
#  openssl des-ecb -K $KEY -in $entry | base64 > orig
#  ./$bin des-ecb -i $entry -k $KEY | base64 > my
#
#  echo -n -e  "$entry " "\t" "$KEY "
#  DIFF=$(diff my orig)
#  if [ "$DIFF" == "" ]
#  then
#      echo -e "${GREEN}Passed!${NC}"
#  else
#      echo -e "${RED}Failed!${NC}"
#  fi
#  rm my orig
#done

################################################################################
# des_ecb pass+salt - encrypt file tests
################################################################################
echo -e "${BLUE}des_ecb pass+salt - encrypt file tests${NC}"
for entry in "test_files"/*
do
  SALT=$(python3 generate_random_salt.py)
  PASSW=$(python3 generate_random_password.py)
  # openssl des-ecb -K $KEY -in $entry | base64 > orig
  openssl des-ecb -S $SALT -pass "pass:$PASSW" -in $entry | base64 > orig
  ./$bin des-ecb -s $SALT -p $PASSW -i $entry | base64 > my

  echo -n -e  "$entry " "\t"
  printf "pass: %-25s salt: %-25s " $PASSW $SALT
  DIFF=$(diff my orig)
  if [[ "$DIFF" == "" ]]
  then
      echo -e "${GREEN}Passed!${NC}"
  else
      echo -e "${RED}Failed!${NC}"
  fi
  rm my orig
done

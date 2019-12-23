#!/bin/bash

bin="../../cmake-build-debug/ft_ssl"
# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

################################################################################
# Base64 File tests
################################################################################
echo -e "${BLUE}Base64 File tests${NC}"
for entry in "testfiles"/*
do
  base64 -i $entry > orig
  ./$bin base64 -i $entry > my

  echo -n "$entry "
  DIFF=$(diff my orig)
  if [ "$DIFF" == "" ]
  then
      echo -e "${GREEN}Passed!${NC}"
  else
      echo -e "${RED}Failed!${NC}"
  fi
  rm my orig
done
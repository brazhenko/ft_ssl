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

################################################################################
# Base64 decode file tests
################################################################################
echo -e "${BLUE}Base64 File tests${NC}"
for entry in "testfiles"/*
do
  base64 -i $entry | base64 -D > orig
  base64 -i $entry | $bin base64 -d > my

  echo -n "$entry "
  DIFF=$(diff my orig)
  if [ "$DIFF" == "" ]
  then
      echo -e "${GREEN}\tPassed!${NC}"
  else
      echo -e "${RED}\tFailed!${NC}"
  fi
  rm my orig
done

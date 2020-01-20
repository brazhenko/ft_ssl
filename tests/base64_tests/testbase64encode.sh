#!/bin/bash

bin="../../cmake-build-debug/ft_ssl"
# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

################################################################################
# Base64 encode file tests
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
      echo -e "${GREEN}\tPassed!${NC}"
  else
      echo -e "${RED}\tFailed!${NC}"
  fi
  rm my orig
done

################################################################################
# Base64 checklist test
################################################################################
echo -e "${BLUE}Base64 checklist test${NC}"
s="repeat after me 'encoding is not encryption'"
echo -n $s
echo $s |  base64  > orig
echo $s | ./$bin base64  > my
DIFF=$(diff my orig)

if [ "$DIFF" == "" ]
then
    echo -e "${GREEN}\tPassed!${NC}"
else
    echo -e "${RED}\tFailed!${NC}"
fi

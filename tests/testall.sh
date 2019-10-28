#!/bin/bash

bin="../ft_ssl"
# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

###############################################################################
# MD5 flag tests
###############################################################################
echo -e "${BLUE}MD5 flag tests${NC}"

echo -n "test1  "
echo "pickle rick" | $bin md5 > my
echo "pickle rick" | md5 > orig
DIFF=$(diff my orig)
if [ "$DIFF" == "" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

echo -n "test2  "
echo "Do not pity the dead, Harry." | $bin md5 -p > my
echo "Do not pity the dead, Harry." | md5 -p > orig
DIFF=$(diff my orig)
if [ "$DIFF" == "" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

echo -n "test3  "
echo "Pity the living." | $bin md5 -q -r > my
echo "Pity the living." | md5 -q -r > orig
DIFF=$(diff my orig)
if [ "$DIFF" == "" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

echo -n "test4  "
echo "And above all," > file
$bin md5 file > my
md5 file > orig
DIFF=$(diff my orig)
if [ "$DIFF" == "" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

echo -n "test5  "
$bin md5 -r file > my
md5 -r file > orig
DIFF=$(diff my orig)
if [ "$DIFF" == "" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

echo -n "test6  "
$bin md5 -s "pity those that aren't following baerista on spotify." > my
md5 -s "pity those that aren't following baerista on spotify." > orig
DIFF=$(diff my orig)
if [ "$DIFF" == "" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

echo -n "test7  "
echo "be sure to handle edge cases carefully" | $bin md5 -p file > my
echo "be sure to handle edge cases carefully" | md5 -p file > orig
DIFF=$(diff my orig)
if [ "$DIFF" == "" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

echo -n "test8  "
echo "some of this will not make sense at first" | $bin md5 file > my
echo "some of this will not make sense at first" | md5 file > orig
DIFF=$(diff my orig)
if [ "$DIFF" == "" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

echo -n "test9  "
echo "but eventually you will understand" | $bin md5 -p -r file > my
echo "but eventually you will understand" | md5 -p -r file > orig
DIFF=$(diff my orig)
if [ "$DIFF" == "" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

echo -n "test10  "
echo "GL HF let's go" | $bin md5 -p -s "foo" file > my
echo "GL HF let's go" | md5 -p -s "foo" file > orig
DIFF=$(diff my orig)
if [ "$DIFF" == "" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

echo -n "test11  "
echo "one more thing" | $bin md5 -r -p -s "foo" file -s "bar" > my 2>&1
echo "one more thing" | md5 -r -p -s "foo" file -s "bar" > orig 2>&1
DIFF=$(diff my orig)
if [ "$DIFF" == "" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo ${DIFF}
    echo -e "${RED}Failed!${NC}"
fi

echo -n "test12  "
echo "just to be extra clear" | $bin md5 -r -q -p -s "foo" file > my
echo "just to be extra clear" | md5 -r -q -p -s "foo" file > orig
DIFF=$(diff my orig)
if [ "$DIFF" == "" ]
then
    echo -e "${GREEN}Passed!${NC}"
else
    echo -e "${RED}Failed!${NC}"
fi

rm my orig
################################################################################

################################################################################
# MD5 File tests
################################################################################
echo -e "${BLUE}MD5 File tests${NC}"
for entry in "test_files"/*
do
  md5 -q $entry > orig
  ./$bin md5 -q $entry > my

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
################################################################################

################################################################################
# SHA256 File tests
################################################################################
echo -e "${BLUE}SHA256 File tests${NC}"
for entry in "test_files"/*
do
  shasum -a 256 $entry |  awk '{ print $1 }' > orig
  ./$bin sha256 -q $entry > my

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
################################################################################

################################################################################
# Hardcore time test
################################################################################
# TODO awk, parse time, benchmarks

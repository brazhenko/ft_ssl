#!/bin/bash

bin="$1"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

###############################################################################
# genrsa test
###############################################################################
echo -e "${BLUE}genrsa tests${NC}"
for VAR in {0..10}
do
	./$bin genrsa -o priv.pem > /dev/null 2>&1
	./$bin rsa -in priv.pem -pubout -out key.pub > /dev/null 2>&1
	openssl rsa -in priv.pem -pubout -out orig.pub > /dev/null 2>&1
	DIFF=$(diff orig.pub key.pub)
	if [ "$DIFF" == "" ]
  then
      echo -e "${GREEN}Passed!${NC}"
  else
      echo -e "${RED}Failed!${NC}"
  fi
done

###############################################################################
# rsa test
###############################################################################
echo -e "${BLUE}rsa key transformation${NC}"

for VAR in {0..10}
do
	openssl genrsa -out priv.pem 64 2>/dev/null
	./$bin rsa -in priv.pem -pubout -out key.pub 2>/dev/null
	openssl rsa -in priv.pem -pubout -out orig.pub 2>/dev/null
	DIFF=$(diff orig.pub key.pub)
	if [ "$DIFF" == "" ]
  then
      echo -e "${GREEN}Passed!${NC}"
  else
      echo -e "${RED}Failed!${NC}"
  fi
done

###############################################################################
# rsa priv test
###############################################################################
echo -e "${BLUE}rsa priv test${NC}"

for VAR in {0..10}
do
	openssl genrsa -out priv.pem 64 2>/dev/null
	./$bin rsa -in priv.pem -out key.pub 2>/dev/null
	openssl rsa -in priv.pem -out orig.pub 2>/dev/null
	DIFF=$(diff orig.pub key.pub)
	if [ "$DIFF" == "" ]
  then
      echo -e "${GREEN}Passed!${NC}"
  else
      echo -e "${RED}Failed!${NC}"
  fi
done

###############################################################################
# pem->der
###############################################################################
echo -e "${BLUE}pem->der private key tests ${NC}"

for VAR in {0..10}
do
	openssl genrsa -out priv.pem 64 2>/dev/null
	./$bin rsa -in priv.pem -outform DER -out key.pub  2>/dev/null
	openssl rsa -in priv.pem -outform DER -out orig.pub 2>/dev/null
	DIFF=$(diff orig.pub key.pub)
	if [ "$DIFF" == "" ]
  then
      echo -e "${GREEN}Passed!${NC}"
  else
      echo -e "${RED}Failed!${NC}"
  fi
done

###############################################################################
# der->pem
###############################################################################
echo -e "${BLUE}der->pem private key tests${NC}"

for VAR in {0..10}
do
	openssl genrsa -out priv.pem 64 2>/dev/null
	openssl rsa -in priv.pem -outform DER -out orig.pub 2>/dev/null
	./$bin rsa -in orig.pub -outform PEM -inform DER -out key.pub  2>/dev/null
	DIFF=$(diff key.pub priv.pem)
	if [ "$DIFF" == "" ]
  then
      echo -e "${GREEN}Passed!${NC}"
  else
      echo -e "${RED}Failed!${NC}"
  fi
done


###############################################################################
# der->pem public
###############################################################################
echo -e "${BLUE}der->pem public key tests ${NC}"

for VAR in {0..10}
do
	openssl genrsa -out priv.pem 64 2>/dev/null
	openssl rsa -in priv.pem -pubout -out test.pem  2>/dev/null
	openssl rsa -in test.pem -pubin -out orig.der -outform DER 2>/dev/null
	./$bin rsa -in orig.der -inform DER -outform PEM -out key.pub -pubin 2>/dev/null
	DIFF=$(diff test.pem key.pub)
	if [ "$DIFF" == "" ]
  then
      echo -e "${GREEN}Passed!${NC}"
  else
      echo -e "${RED}Failed!${NC}"
  fi
done

###############################################################################
# pem->der public
###############################################################################
echo -e "${BLUE}der->pem public key tests${NC}"

for VAR in {0..10}
do
	openssl genrsa -out priv.pem 64 2>/dev/null
	openssl rsa -in priv.pem -pubout -out test.pem  2>/dev/null
	openssl rsa -in test.pem -pubin -out orig.der -outform DER 2>/dev/null
	./$bin rsa -in test.pem -outform DER -out key.pub.der -pubin 2>/dev/null
	DIFF=$(diff key.pub.der orig.der)
	if [ "$DIFF" == "" ]
  then
      echo -e "${GREEN}Passed!${NC}"
  else
      echo -e "${RED}Failed!${NC}"
  fi
done

################################################################################
# rsa encrypt/decrypt tests
################################################################################
echo -e "${BLUE}rsa encrypt/decrypt tests${NC}"
for entry in "test_files"/*
do
  ./$bin genrsa -o main.key > /dev/null 2>&1
  ./$bin rsa -pubout -out main.pub -in main.key > /dev/null 2>&1
  ./$bin rsautl -encrypt -in "$entry" -out crypto.txt -pubin -inkey main.pub > /dev/null 2>&1
  ./$bin  rsautl -decrypt -inkey main.key -in crypto.txt -out answer > /dev/null 2>&1

  #echo  "$entry "
  DIFF=$(diff "$entry" answer)
  if [ "$DIFF" == "" ]
  then
      echo -e "${GREEN}Passed!${NC}"
  else
      echo -e "${RED}Failed!${NC}"
  fi
done


find . -depth 1 -type f -not -name '*.sh' -delete
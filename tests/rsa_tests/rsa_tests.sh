#!/bin/bash

bin="../../cmake-build-debug/ft_ssl"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

###############################################################################
# genrsa test
###############################################################################
for VAR in {0..50}
do
	./$bin genrsa -o priv.pem 2>/dev/null
	openssl rsa -in priv.pem -pubout -out  orig.pub 2>/dev/null
	DIFF=$(diff orig.pub key.pub)
	if [ "$DIFF" == "" ]
  then
      echo -e "${GREEN}Passed!${NC}"
  else
      echo -e "${RED}Failed!${NC}"
  fi
done

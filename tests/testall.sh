#!/bin/bash

export bin=$1

cd base64_tests
pwd
./testall.sh "../$1"
cd ..

cd des_tests
pwd
./test_all.sh "../$1"
cd ..

cd hash_tests
./testmd5sha256.sh "../$1"
cd ..

cd rsa_tests
./rsa_tests.sh "../$1"
cd ..
echo Done!
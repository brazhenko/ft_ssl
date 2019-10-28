#!/bin/bash

bin="ft_ssl"

for entry in "test_files"/*
do
  md5 -q $entry > orig_result
  ./$bin md5 -q $entry > my_result
  diff orig_result my_result
  echo "$entry "
done
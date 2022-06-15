#!/bin/sh
  lab=lab09-hchan
  rm -f diff.txt; touch diff.txt
  echo "================================================================================" >> diff.txt
  for file in \
pnet_refined.cpp \
    ; do
    echo "diff ../../sources/${lab}/${file} ${file} >> diff.txt" >> diff.txt
          diff ../../sources/${lab}/${file} ${file} >> diff.txt
    echo "================================================================================" >> diff.txt
  done

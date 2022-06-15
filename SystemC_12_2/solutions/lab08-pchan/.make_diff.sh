#!/bin/sh
  lab=lab08-pchan
  rm -f diff.txt; touch diff.txt
  echo "================================================================================" >> diff.txt
  for file in \
pnet_chan.h \
pnet_chan.cpp \
pnet_sync.h \
    ; do
    echo "diff ../../sources/${lab}/${file} ${file} >> diff.txt" >> diff.txt
          diff ../../sources/${lab}/${file} ${file} >> diff.txt
    echo "================================================================================" >> diff.txt
  done

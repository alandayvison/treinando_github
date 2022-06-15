#!/bin/sh

  path=`pwd`
  lab=`basename $path`

  ../sources/${lab}/.make_new.sh

  rm -fr results.txt > /dev/null 2>&1
  touch results.txt

  execute () {
     echo "$1 >> $2 2>&1" >> results.txt
     echo "$1 >> $2 2>&1"
     $1 >> $2 2>&1 || {
       echo "#FAIL: ${lab}: $1 >> $2 2>&1" >> results.txt
       echo "#FAIL: ${lab}: $1 >> $2 2>&1"
       exit 1
      }
  }

  echo ""
  execute "rm -fr xcelium.d *.log" "/dev/null"
  execute "xrun fifo_test.cpp -log_xmsim xmsim.log -q -sysc" "/dev/null"
  execute "diff ../solutions/$lab/xmsim.log xmsim.log" "/dev/null"
  echo "" >> results.txt ; echo ""

  echo "#PASS: $lab" >> results.txt
  echo "#PASS: $lab"

  cp *.log results.txt ../solutions/$lab/

  echo ""

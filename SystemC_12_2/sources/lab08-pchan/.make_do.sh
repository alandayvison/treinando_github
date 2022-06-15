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
  execute "cp ../solutions/$lab/*.h   ."     "/dev/null"
  execute "cp ../solutions/$lab/*.cpp ."     "/dev/null"
  echo "" >> results.txt ; echo ""

  execute "rm -fr xcelium.d *.log"           "/dev/null"
  execute "xrun pnet_sync_test.cpp -log_xmsim xmsim1.log -q -sysc" "/dev/null"
  execute "diff ../solutions/$lab/xmsim1.log xmsim1.log" "/dev/null"
  echo "" >> results.txt ; echo ""

  execute "rm -fr xcelium.d *.log"           "/dev/null"
  execute "xrun -f xrun_args.txt -log_xmsim xmsim2.log -q -sysc" "/dev/null"
  execute "diff ../solutions/$lab/xmsim2.log xmsim2.log" "/dev/null"
  echo "" >> results.txt ; echo ""

  echo "#PASS: $lab" >> results.txt
  echo "#PASS: $lab"

  cp *.log results.txt ../solutions/$lab/

  echo ""

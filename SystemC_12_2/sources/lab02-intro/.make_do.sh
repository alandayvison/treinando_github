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
       cd ..
       exit 1
      }
  }

  exec_up () {
     echo "$1 >> $2 2>&1" >> ../results.txt
     echo "$1 >> $2 2>&1"
     $1 >> $2 2>&1 || {
       echo "#FAIL: ${lab}: $1 >> $2 2>&1" >> ../results.txt
       echo "#FAIL: ${lab}: $1 >> $2 2>&1"
       cd ..
       exit 1
      }
  }

  echo ""

  execute "cp -r `xmroot`/tools/systemc/examples/systemc_only/ ." "/dev/null"
  cd systemc_only
  exec_up "xrun -f run.f -q" "/dev/null"
  cd ..
  execute "diff systemc_only/xmsim.au systemc_only/xmsim.log" "/dev/null"
  echo "" >> results.txt ; echo ""

  execute "cp -r `xmroot`/doc/xmsctut1/example/ ." "/dev/null"
  cd example
  exec_up "xrun *.cpp -log_xmsim xmsim.log -q -sysc -top test_drink" "/dev/null"
  cd ..
  execute "diff ../solutions/${lab}/xmsim.log example/xmsim.log" "/dev/null"

  echo "" >> results.txt ; echo ""

  echo "#PASS: $lab" >> results.txt
  echo "#PASS: $lab"

  cp results.txt  ../solutions/$lab/

  echo ""

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

  execute "cp -r `xmroot`/doc/xmsctut2/example/ ." "/dev/null"
  cd example
  exec_up "xrun *.cpp *.v -log_xmsim xmsim.log -q -sysc -top scMain" "/dev/null"
  cd ..
  execute "grep Monitor.final.event.count:.40 example/xmsim.log" "/dev/null"

  echo "" >> results.txt ; echo ""

  echo "#PASS: $lab" >> results.txt
  echo "#PASS: $lab"

  cp example/xrun.log example/xmsim.log ../solutions/$lab/
  cp results.txt  ../solutions/$lab/

  echo ""

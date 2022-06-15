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
  execute "cp ../solutions/$lab/*.cpp ."   "/dev/null"
  execute "rm -f scsim.exe *.log *.tmp"    "/dev/null"
  echo "" >> results.txt ; echo ""

  execute "${SCCC} *.cpp -g -o scsim.exe -I${SYSTEMC}/include -L${SYSTEMC}/lib-${TARGET_ARCH} -lsystemc" "g++.log"
  execute "scsim.exe" "scsim.log"
  execute "tail -236 ../solutions/$lab/scsim.log" "scsim_old.log.tmp"
  execute "tail -236                   scsim.log" "scsim_new.log.tmp"
  execute "diff scsim_old.log.tmp scsim_new.log.tmp" "/dev/null"
  echo "" >> results.txt ; echo ""

  echo "#PASS: $lab" >> results.txt
  echo "#PASS: $lab"

  cp *.log results.txt ../solutions/$lab/

  echo ""

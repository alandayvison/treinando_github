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
  echo "Nothing to do" >> results.txt
  echo "Nothing to do"
  echo "" >> results.txt ; echo ""

  echo "#PASS: $lab" >> results.txt
  echo "#PASS: $lab"

  cp results.txt  ../solutions/$lab/

  echo ""

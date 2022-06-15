#!/bin/sh

  rm -fr results.txt > /dev/null 2>&1
  touch results.txt
  fail=0

  for lab in lab* ; do
    if cd $lab ; then
      if ../sources/$lab/.make_new.sh >> ../results.txt 2>&1 ; then
        echo "MADE: $lab" >> ../results.txt
        echo "MADE: $lab"
      else
        echo "FAIL: $lab" >> ../results.txt
        echo "FAIL: $lab"
        fail=1
      fi
      cd ..
    else
      echo "FAIL: Can't cd $lab" >> results.txt
      echo "FAIL: Can't cd $lab"
      fail=1
    fi
  done

  if [ ${fail} != 0 ] ; then
    echo "LAB FAILURE" >> results.txt
    echo "LAB FAILURE"
    exit 1
  fi

  echo "ALL LABS MADE" >> results.txt
  echo "ALL LABS MADE"


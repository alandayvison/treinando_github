#!/bin/sh

  rm -fr results.txt > /dev/null 2>&1
  touch results.txt
  fail=0

  for lab in lab* ; do
    [ $lab == "lab01-help"  ] && continue
    [ $lab == "lab02-intro" ] && continue
    [ $lab == "lab11-debug" ] && continue
    if cd $lab ; then
      if ../sources/$lab/.make_sc.sh >> ../results.txt 2>&1 ; then
        echo "PASS: $lab" >> ../results.txt
        echo "PASS: $lab"
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

  echo "ALL LABS PASS" >> results.txt
  echo "ALL LABS PASS"


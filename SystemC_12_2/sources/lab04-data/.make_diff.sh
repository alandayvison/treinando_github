#!/bin/sh
  prevlab="lab03-lang"
  rm -f diff.txt; touch diff.txt

  echo "" >> diff.txt
  echo "THIS LAB 4 SOURCE SET SHOULD BE IDENTICAL TO THE LAB 3 SOURCE SET" >> diff.txt
  echo "================================================================================" >> diff.txt
  for file in \
pnet_cpu.cpp     \
pnet_cpu.h       \
pnet_monitor.cpp \
pnet_monitor.h   \
pnet_node.cpp    \
sc_main.cpp      \
    ; do
    echo "diff ../${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
          diff ../${prevlab}/${file} ${file} >> diff.txt
    echo "================================================================================" >> diff.txt
  done

#  echo "" >> diff.txt
#  echo "THIS LAB 4 SOURCE SET SHOULD BE IDENTICAL TO THE LAB 3 SOLUTION SET" >> diff.txt
#    echo "================================================================================" >> diff.txt
#  for file in \
#    ; do
#    echo "diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
#          diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt
#    echo "================================================================================" >> diff.txt
#  done

  echo "" >> diff.txt
  echo "THIS LAB 4 SOURCE SET SHOULD BE DIFFERENT THAN THE LAB 3 SOURCE SET" >> diff.txt
    echo "================================================================================" >> diff.txt
  for file in \
xrun_args.txt   \
pnet_chan.h     \
pnet_node.h     \
pnet_system.h   \
pnet_system.cpp \
    ; do
    echo "diff ../${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
          diff ../${prevlab}/${file} ${file} >> diff.txt
    echo "================================================================================" >> diff.txt
  done

  echo "" >> diff.txt
  echo "THIS LAB 4 SOURCE SET SHOULD BE DIFFERENT THAN THE LAB 3 SOLUTION SET" >> diff.txt
    echo "================================================================================" >> diff.txt
  for file in \
pnet_chan.cpp \
    ; do
    echo "diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
          diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt
    echo "================================================================================" >> diff.txt
  done

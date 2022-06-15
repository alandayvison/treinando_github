#!/bin/sh
  prevlab="lab06-ifcp"
  rm -f diff.txt; touch diff.txt

  echo "" >> diff.txt
  echo "THIS LAB 8 SOURCE SET SHOULD BE IDENTICAL TO THE LAB 6 SOURCE SET" >> diff.txt
  echo "================================================================================" >> diff.txt
  for file in \
pnet_cpu.cpp     \
pnet_cpu.h       \
pnet_frame.cpp   \
pnet_frame.h     \
pnet_ifs.h       \
pnet_monitor.cpp \
pnet_monitor.h   \
pnet_node.cpp    \
pnet_node.h      \
pnet_system.cpp  \
pnet_system.h    \
sc_main.cpp      \
xrun_args.txt    \
    ; do
    echo "diff ../${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
          diff ../${prevlab}/${file} ${file} >> diff.txt
    echo "================================================================================" >> diff.txt
  done

  echo "" >> diff.txt
  echo "THIS LAB 8 SOURCE SET SHOULD BE IDENTICAL TO THE LAB 6 SOLUTION SET" >> diff.txt
    echo "================================================================================" >> diff.txt
  for file in \
pnet_chan.h   \
pnet_chan.cpp \
    ; do
    echo "diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
          diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt
    echo "================================================================================" >> diff.txt
  done

#  echo "" >> diff.txt
#  echo "THIS LAB 8 SOURCE SET SHOULD BE DIFFERENT THAN THE LAB 6 SOURCE SET" >> diff.txt
#    echo "================================================================================" >> diff.txt
#  for file in \
#    ; do
#    echo "diff ../${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
#          diff ../${prevlab}/${file} ${file} >> diff.txt
#    echo "================================================================================" >> diff.txt
#  done

#  echo "" >> diff.txt
#  echo "THIS LAB 8 SOURCE SET SHOULD BE DIFFERENT THAN THE LAB 6 SOLUTION SET" >> diff.txt
#    echo "================================================================================" >> diff.txt
#  for file in \
#    ; do
#    echo "diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
#          diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt
#    echo "================================================================================" >> diff.txt
#  done

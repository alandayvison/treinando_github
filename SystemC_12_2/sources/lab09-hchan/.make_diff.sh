#!/bin/sh
  prevlab="lab08-pchan"
  rm -f diff.txt; touch diff.txt

  echo "" >> diff.txt
  echo "THIS LAB 9 SOURCE SET SHOULD BE IDENTICAL TO THE LAB 8 SOURCE SET" >> diff.txt
  echo "================================================================================" >> diff.txt
  for file in \
pnet_cpu.h       \
pnet_frame.cpp   \
pnet_frame.h     \
pnet_ifs.h       \
pnet_monitor.cpp \
pnet_monitor.h   \
pnet_sync_ifs.h  \
pnet_system.cpp  \
pnet_system.h    \
sc_main.cpp      \
    ; do
    echo "diff ../${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
          diff ../${prevlab}/${file} ${file} >> diff.txt
    echo "================================================================================" >> diff.txt
  done

  echo "" >> diff.txt
  echo "THIS LAB 9 SOURCE SET SHOULD BE IDENTICAL TO THE LAB 8 SOLUTION SET" >> diff.txt
    echo "================================================================================" >> diff.txt
  for file in \
pnet_sync.h      \
    ; do
    echo "diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
          diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt
    echo "================================================================================" >> diff.txt
  done

  echo "" >> diff.txt
  echo "THIS LAB 9 SOURCE SET SHOULD BE DIFFERENT THAN THE LAB 8 SOURCE SET" >> diff.txt
    echo "================================================================================" >> diff.txt
  for file in \
xrun_args.txt \
pnet_cpu.cpp  \
pnet_node.h   \
pnet_node.cpp \
    ; do
    echo "diff ../${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
          diff ../${prevlab}/${file} ${file} >> diff.txt
    echo "================================================================================" >> diff.txt
  done

#  echo "" >> diff.txt
#  echo "THIS LAB 9 SOURCE SET SHOULD BE DIFFERENT THAN THE LAB 8 SOLUTION SET" >> diff.txt
#    echo "================================================================================" >> diff.txt
#  for file in \
#    ; do
#    echo "diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
#          diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt
#    echo "================================================================================" >> diff.txt
#  done

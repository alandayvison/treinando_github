#!/bin/sh
  prevlab="lab09-hchan"
  rm -f diff.txt; touch diff.txt

  echo "" >> diff.txt
  echo "THIS LAB 10 SOURCE SET SHOULD BE IDENTICAL TO THE LAB 9 SOURCE SET" >> diff.txt
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
pnet_refined.h   \
pnet_sync.h      \
pnet_sync_ifs.h  \
pnet_system.cpp  \
pnet_system.h    \
pnet_trans.cpp   \
pnet_trans.h     \
pnet_wrap.h      \
    ; do
    echo "diff ../${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
          diff ../${prevlab}/${file} ${file} >> diff.txt
    echo "================================================================================" >> diff.txt
  done

  echo "" >> diff.txt
  echo "THIS LAB 10 SOURCE SET SHOULD BE IDENTICAL TO THE LAB 9 SOLUTION SET" >> diff.txt
    echo "================================================================================" >> diff.txt
  for file in \
pnet_refined.cpp \
    ; do
    echo "diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
          diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt
    echo "================================================================================" >> diff.txt
  done

  echo "" >> diff.txt
  echo "THIS LAB 10 SOURCE SET SHOULD BE DIFFERENT THAN THE LAB 9 SOURCE SET" >> diff.txt
    echo "================================================================================" >> diff.txt
  for file in \
xrun_args.txt \
sc_main.cpp   \
    ; do
    echo "diff ../${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
          diff ../${prevlab}/${file} ${file} >> diff.txt
    echo "================================================================================" >> diff.txt
  done

#  echo "" >> diff.txt
#  echo "THIS LAB 10 SOURCE SET SHOULD BE DIFFERENT THAN THE LAB 9 SOLUTION SET" >> diff.txt
#    echo "================================================================================" >> diff.txt
#  for file in \
#    ; do
#    echo "diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt" >> diff.txt
#          diff ../../solutions/${prevlab}/${file} ${file} >> diff.txt
#    echo "================================================================================" >> diff.txt
#  done

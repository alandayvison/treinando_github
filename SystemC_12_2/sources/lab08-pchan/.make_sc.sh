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
  execute "cp ../solutions/$lab/*.h   ."   "/dev/null"
  execute "cp ../solutions/$lab/*.cpp ."   "/dev/null"
  execute "rm -f scsim.exe *.log *.tmp"    "/dev/null"
  echo "" >> results.txt ; echo ""

  execute "${SCCC} pnet_sync_test.cpp -g -o scsim.exe -I${SYSTEMC}/include -L${SYSTEMC}/lib-${TARGET_ARCH} -lsystemc" "g++1.log"
  execute "scsim.exe" "scsim1.log"
  execute "tail -32 ../solutions/$lab/scsim1.log" "scsim_old1.log.tmp"
  execute "tail -32                   scsim1.log" "scsim_new1.log.tmp"
  execute "diff scsim_old1.log.tmp scsim_new1.log.tmp" "/dev/null"
  echo "" >> results.txt ; echo ""

  execute "${SCCC} pnet_frame.cpp pnet_chan.cpp pnet_cpu.cpp pnet_node.cpp pnet_monitor.cpp pnet_system.cpp sc_main.cpp -g -o scsim.exe -I${SYSTEMC}/include -L${SYSTEMC}/lib-${TARGET_ARCH} -lsystemc" "g++2.log"
  execute "scsim.exe" "scsim2.log"
  execute "tail -5 ../solutions/$lab/scsim2.log" "scsim_old2.log.tmp"
  execute "tail -5                   scsim2.log" "scsim_new2.log.tmp"
  execute "diff scsim_old2.log.tmp scsim_new2.log.tmp" "/dev/null"
  echo "" >> results.txt ; echo ""

  echo "#PASS: $lab" >> results.txt
  echo "#PASS: $lab"

  cp *.log results.txt ../solutions/$lab/

  echo ""

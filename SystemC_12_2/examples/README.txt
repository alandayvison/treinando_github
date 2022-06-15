  setenv SCCC /usr/bin/g++
  setenv SYSTEMC /cds1/systemc-2.3.3
  setenv TARGET_ARCH linux64
  setenv LD_LIBRARY_PATH .:${SYSTEMC}/lib-${TARGET_ARCH}:${LD_LIBRARY_PATH}
  ${SCCC} test.cpp -g -o scsim.exe -I${SYSTEMC}/include -L${SYSTEMC}/lib-${TAR
GET_ARCH} -lsystemc > g++.log
  scsim.exe > scsim.log
  rm g++.log scsim.exe scsim.log

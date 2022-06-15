////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2012 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : sc_main.cpp                                                  //
// Project     : SystemC Language Fundamentals                                //
// Description : FIFO demonstration                                           //
// Notes       : To reduce indeterminancy, your interprocess communication    //
//               should occur through primitive channels that delay the       //
//               communication by one delta cycle. The SystemC fifo channel:  //
//               Makes num_free() to the writer immediately as it becomes     //
//               zero and with a delta-cycle delay as it becomes non-zero.    //
//               Makes num_available() to the reader immediately as it becomes//
//               zero and with a delta-cycle delay as it becomes non-zero.    //
// Change Log  : 2011-04-30 mikep Created.                                    //
//               2012-09-23 mikep Added sc_stop() call for SimVision.         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include "systemc.h"

SC_MODULE ( fifo_test ) {
  sc_fifo<int> fifo ;
  SC_CTOR ( fifo_test )
  : fifo ( "fifo", 2 )
  { SC_THREAD ( test_proc ) ; }
  void test_proc ( ) {
    SC_FORK
      sc_spawn ( sc_bind(&fifo_test::write,this), "writeproc" ),
      sc_spawn ( sc_bind(&fifo_test::read, this), "readproc"  ) 
    SC_JOIN
     wait ( 1, SC_NS ) ;
    SC_FORK
      sc_spawn ( sc_bind(&fifo_test::read, this), "readproc"  ),
      sc_spawn ( sc_bind(&fifo_test::write,this), "writeproc" ) 
    SC_JOIN
  }
  void write ( ) {
    int data[] = {42,86,911} ;
    cout << "time: " << sc_simulation_time()
         << ", cycle: " << sc_delta_count()
         << " Write process started" << endl ;
    for(int i=0;i<=2;++i) {
      fifo.write ( data[i] ) ;
      cout << "time: " << sc_simulation_time()
           << ", cycle: " << sc_delta_count()
           << " Write process wrote data " << data[i] << endl ;
    }
  }
  void read ( ) {
    int data ;
    cout << "time: " << sc_simulation_time()
         << ", cycle: " << sc_delta_count()
         << " Read  process started" << endl ;
    for(int i=0;i<=2;++i) {
      fifo.read ( data ) ;
      cout << "time: " << sc_simulation_time()
           << ", cycle: " << sc_delta_count()
           << " Read  process read  data " << data << endl ;
    }
  }
} ;

int sc_main ( int argc, char ** argv ) {
  fifo_test test ( "test" ) ;
  sc_start ( ) ;
  sc_stop ( ) ;
  return 0 ;
}

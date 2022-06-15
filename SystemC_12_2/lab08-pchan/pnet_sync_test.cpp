////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : sync_test.cc                                                 //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET sync primitive channel test                             //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include "systemc.h"
#include "pnet_sync.h"

SC_MODULE ( sync_test ) {
  pnet_sync<int> sync ;
  int value ;
  sc_process_handle handle ;
  SC_CTOR ( sync_test )
  : sync ( "sync" )
  { SC_THREAD ( test_proc ) ; }
  void test_proc ( ) {
    cout << "START OF SYNC TEST" << endl ;
    cout << "Assert number free not 0" << endl ;
    sc_assert ( sync.num_free() != 0 ) ;
    cout << "Assert number available is 0" << endl ;
    sc_assert ( sync.num_available() == 0 ) ;
    cout << "Assert nonblocking write succeeds" << endl ;
    sc_assert ( sync.nb_write(42) ) ;
    sc_assert ( sync.num_free() == 0 ) ;
    cout << "Assert channel not yet updated" << endl ;
    sc_assert ( sync.num_available() == 0 ) ;
    cout << "Wait for data_written_event" << endl ;
    wait ( 1, SC_NS, sync.data_written_event() ) ;
    cout << "Assert wait did not time out" << endl ;
    sc_assert ( !timed_out() ) ;
    cout << "Assert channel is updated" << endl ;
    sc_assert ( sync.num_free() == 0 ) ;
    sc_assert ( sync.num_available() != 0 ) ;
    cout << "Assert nonblocking read succeeds" << endl ;
    value = -1 ;
    sc_assert ( sync.nb_read(value) ) ;
    sc_assert ( sync.num_available() == 0 ) ;
    cout << "Assert stored value is correct" << endl ;
    sc_assert ( value == 42 ) ;
    cout << "Assert channel not yet updated" << endl ;
    sc_assert ( sync.num_free() == 0 ) ;
    cout << "Wait for data_read_event" << endl ;
    wait ( 1, SC_NS, sync.data_read_event() ) ;
    cout << "Assert wait did not time out" << endl ;
    sc_assert ( !timed_out() ) ;
    cout << "Assert channel is updated" << endl ;
    sc_assert ( sync.num_free() != 0 ) ;
    sc_assert ( sync.num_available() == 0 ) ;
    cout << "Attempt blocking write" << endl ;
    value = 911 ;
    handle = sc_spawn ( sc_bind(&sync_test::write,this) ) ;
    cout << "Wait for write to complete" << endl ;
    wait ( 1, SC_NS, handle.terminated_event() ) ;
    cout << "Assert wait did not time out" << endl ;
    sc_assert ( !timed_out() ) ;
    cout << "Attempt blocking read" << endl ;
    value = -1 ;
    handle = sc_spawn ( sc_bind(&sync_test::read,this) ) ;
    cout << "Wait for read to complete" << endl ;
    wait ( 1, SC_NS, handle.terminated_event() ) ;
    cout << "Assert wait did not time out" << endl ;
    sc_assert ( !timed_out() ) ;
    cout << "Assert stored value is correct" << endl ;
    sc_assert ( value == 911 ) ;
    cout << "END OF SYNC TEST" << endl ;
  }
  void write ( ) { sync.write ( value ) ; }
  void read  ( ) { sync.read  ( value ) ; }
} ;

int sc_main ( int argc, char **argv ) {
  sync_test test ( "test" ) ;
  sc_start ( ) ;
  return 0 ;
}
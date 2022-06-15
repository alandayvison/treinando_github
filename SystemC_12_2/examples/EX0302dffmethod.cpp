////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0302method.cpp                                             //
// Title       : The Method Process                                           //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrate statically registering a method process          //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef DFF_H
#define DFF_H
#include "systemc.h"
SC_MODULE ( dff ) {
  // Declarations
  sc_out <bool> q ;
  sc_in  <bool> c, d, r ;
  void dff_method() {
      q = r ? 0 : d ;
  }
  // Constructor
  SC_CTOR ( dff ) {
    // Process registration
    SC_METHOD ( dff_method ) ;
      sensitive << c.pos() ;
      dont_initialize() ;
  }
} ;
#endif

#ifndef DFF_TEST_H
#define DFF_TEST_H
#include "systemc.h"
// #include "dff.h"
SC_MODULE ( dff_test ) {
  sc_in <bool> c ;
  sc_signal <bool> q, d, r ;
  dff dff_inst ;
  SC_CTOR ( dff_test )
  :
    c ( "c" ) ,
    q ( "q" ) ,
    d ( "d" ) ,
    r ( "r" ) ,
    dff_inst ( "dff_inst" )  
  {
    dff_inst ( q, c, d, r ) ;
    SC_THREAD ( test_thread ) ;
      sensitive << c.neg() ;
      dont_initialize() ;
  }
  void test_thread() {
    d = 0 ; r = 1 ;
    wait() ;
    d = 1 ; r = 0 ;
    wait() ;
    d = 0 ;
    wait() ;
    sc_stop() ;
  }
} ;
#endif

#include "systemc.h"
// #include "dff_test.h"
int sc_main ( int argc, char **argv ) {
  sc_clock clock ( "clock" ) ;
  dff_test test  ( "test"  ) ;
  test ( clock ) ;
  sc_start() ;
  return 0;
}
